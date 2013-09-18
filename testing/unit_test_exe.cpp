#ifdef _MSC_VER
#define _CRTDBG_MAP_ALLOC
#include <stdlib.h>
#include <crtdbg.h>
#include <iostream>
#include <sstream>
namespace{
	struct MemLeakCheckInit{
		MemLeakCheckInit(){
			_CrtSetDbgFlag(_CRTDBG_ALLOC_MEM_DF | _CRTDBG_LEAK_CHECK_DF);
			//_crtBreakAlloc = 3562;
		}
	};

	MemLeakCheckInit mlcinit;
}

#endif

#include <mutex>
#include <thread>
#include "../cppcomponents_libuv/cppcomponents_libuv.hpp"
#include <cppcomponents_async_coroutine_wrapper/cppcomponents_resumable_await.hpp>

#define CATCH_CONFIG_MAIN  
#include "external/catch.hpp"

namespace luv = cppcomponents_libuv;
using cppcomponents::use;

const int TEST_PORT = 7171;


TEST_CASE("test-async", "test-async"){
		int prepare_cb_called = 0;
	int async_cb_called = 0;
	int close_cb_called = 0;

	std::thread thread;
	std::mutex mutex;
	mutex.lock();

	auto loop = luv::Loop::DefaultLoop();
	luv::Prepare prepare{ loop };


	auto close_cb = [&](cppcomponents::Future<void>){
		close_cb_called++;
	};

	auto async_cb = [&](use<luv::IAsync> async, int status){
		REQUIRE(status == 0);

		mutex.lock();
		int n = ++async_cb_called;
		mutex.unlock();

		if (n >= 3){
			async.Close().Then(close_cb);
			prepare.Close().Then(close_cb);
		}

	};
	luv::Async async{loop,async_cb};


	auto thread_cb = [&](){
		int n;
		for (;;){
			mutex.lock();
			n = async_cb_called;
			mutex.unlock();

			if (n == 3){
				break;
			}
			async.Send();

			std::this_thread::sleep_for(std::chrono::milliseconds(0));

		}

	};





	auto prepare_cb = [&](use<luv::IPrepare> p, int status){
		REQUIRE(status == 0);
		if (prepare_cb_called++)
			return;

		thread = std::thread(thread_cb);

		mutex.unlock(); 

	};

	prepare.Start(prepare_cb);

	loop.Run();

	REQUIRE(prepare_cb_called > 0);

	REQUIRE(async_cb_called == 3);
	REQUIRE(close_cb_called == 2);

	thread.join();



	


}


TEST_CASE("test-connection-fail", "test-connection-fail"){

	auto loop = luv::Loop::DefaultLoop();
	use<luv::ITcpStream> tcp;
	//static uv_connect_t req;
	int connect_cb_calls = 0;
	int close_cb_calls = 0;

	use<luv::ITimer> timer;
	int timer_close_cb_calls = 0;
	int timer_cb_calls = 0;

	auto on_close = [&](cppcomponents::Future<void>){
		close_cb_calls++;
	};

	auto timer_close_cb = [&](cppcomponents::Future<void>){
		timer_close_cb_calls++;
	};

	auto timer_cb = [&](use<luv::ITimer>, int status){
		REQUIRE(status == 0);
		timer_cb_calls++;

		REQUIRE(close_cb_calls == 0);
		REQUIRE(connect_cb_calls == 1);

		tcp.Close().Then(on_close);
		timer.Close().Then(timer_close_cb);
	};

	auto on_connect_with_close = [&](cppcomponents::Future<int> fut) {
		auto status = fut.ErrorCode();
		REQUIRE(status == luv::ErrorCodes::Connrefused);
		connect_cb_calls++;

		REQUIRE(close_cb_calls == 0);
		tcp.Close().Then(on_close);
	};

	auto on_connect_without_close = [&](cppcomponents::Future<int> fut){
		auto status = fut.ErrorCode();
		REQUIRE(status == luv::ErrorCodes::Connrefused);
		connect_cb_calls++;
		timer.Start(timer_cb, 100, 0);
		REQUIRE(close_cb_calls == 0);
	};

	auto connection_fail = 
		[&](std::function < void(cppcomponents::Future<int> fut)> connect_cb){

			auto client_addr = luv::Uv::Ip4Addr("0.0.0.0", 0);
			
			auto server_addr = luv::Uv::Ip4Addr("127.0.0.1", TEST_PORT);

			tcp = luv::TcpStream{ loop };

			tcp.Bind(client_addr);
			tcp.Connect(server_addr).Then(connect_cb);

			loop.Run();

			REQUIRE(connect_cb_calls == 1);
			REQUIRE(close_cb_calls == 1);

	};

	auto test_impl_connection_fail = [&](){
		connection_fail(on_connect_with_close);

		REQUIRE(timer_close_cb_calls == 0);
		REQUIRE(timer_cb_calls == 0);
	};

	auto test_impl_connection_fail_doesnt_auto_close = [&]() {

		timer = luv::Timer{ loop };

		connection_fail(on_connect_without_close);

		REQUIRE(timer_close_cb_calls == 1);
		REQUIRE(timer_cb_calls == 1);

	};

	test_impl_connection_fail();

	connect_cb_calls = 0;

	// Reset the counters
	close_cb_calls = 0;

	timer_close_cb_calls = 0;
	timer_cb_calls = 0;
	test_impl_connection_fail_doesnt_auto_close();

}

TEST_CASE("TCP", "TcpStream"){

	auto loop = luv::Loop{};


	luv::TcpStream server{ loop };

	auto server_addr = luv::Uv::Ip4Addr("0.0.0.0", TEST_PORT);

	server.Bind(server_addr);


	luv::Executor executor{ loop };

		server.Listen(1,cppcomponents::resumable<void>([&](use<luv::IStream> stream, int,cppcomponents::awaiter<void> await){


			luv::TcpStream client{ loop };
			stream.Accept(client);
			auto readchan = client.ReadStartWithChannel();

			int k = 0;
			while (true){
				auto fut = await.as_future(executor,readchan.Read());
				if (fut.ErrorCode()){
					break;
				}
				auto buf = fut.Get();
				std::string s{ buf.Begin(), buf.End() };
				REQUIRE(s == "Hello");
				std::stringstream strstream;
				strstream << "Hi " << k++;
				std::string response = strstream.str();
				await(executor,client.Write(response));
			}
		}));


		auto client_func = cppcomponents::resumable<void>([&](cppcomponents::awaiter<void> await){
			for (int i = 0; i < 4; i++){
				auto client_address = luv::Uv::Ip4Addr("127.0.0.1", TEST_PORT);
				luv::TcpStream client{ loop };
				await(executor,client.Connect(client_address));
				auto chan = client.ReadStartWithChannel();
				await(executor,client.Write(std::string("Hello")));
				auto buf = await(executor,chan.Read());
				std::string response{ buf.Begin(), buf.End() };
				REQUIRE(std::string("Hi 0") == response);
				await(client.Write(std::string("Hello")));
				buf = await(executor,chan.Read());
				response.assign( buf.Begin(), buf.End() );
				REQUIRE(std::string("Hi 1") == response);
			}


			server.Close();
			executor.Stop();


		});

		client_func();
	loop.Run();


	

} 

#include <fcntl.h>
#include <sys/stat.h>

TEST_CASE("fs", "fs1"){

	luv::Loop loop;

	luv::LoopFile file{ loop };

	auto func = cppcomponents::resumable<void>([&](cppcomponents::awaiter<void> await){
		auto cwd = luv::Uv::Cwd();

		// Make a file
		std::string dir = "./testdir/";
		std::string filename = "./testdir/testfile.txt";

		// Create a directory
		await(file.Mkdir(dir, O_CREAT));

		// Create a file in the directory
		await(file.Open(filename, O_CREAT | O_RDWR, S_IWRITE|S_IREAD));


		// Write some data
		std::string out = "Hello World";
		await(file.Write(out.data(), out.size(), 0));

		// Sync and close
		await(file.Sync());
		await(file.Close());

		// Open it again
		await(file.Open(filename, O_RDONLY, 0));
		std::vector<char> buf(100);

		// Read from it
		auto sz = await(file.Read(&buf[0], buf.size(), 0));
		std::string in{ buf.begin(), buf.begin() + sz };
		REQUIRE(out == in);

		await(file.Close());

		await(file.Open(filename, O_WRONLY, 0));

		// Truncate it
		await(file.Truncate(5));

		// Close it
		await(file.Close());

		// Open it again
		await(file.Open(filename, O_RDONLY, 0));

		// Check out truncated read
		sz = await(file.Read(&buf[0], buf.size(), 0));
		in.assign(buf.begin(), buf.begin() + sz);
		REQUIRE(in == "Hello");
		await(file.Close());

		// Stat it
		auto stat = await(file.Stat(filename));
		REQUIRE(stat.st_size == 5);

		// Check that it is in the directory
		auto dirfiles = await(file.Readdir(dir,0));
		REQUIRE(dirfiles.size() == 1);
		REQUIRE(dirfiles[0] == "testfile.txt");

		// Delete the file
		await(file.Unlink(filename));

		// Check that it is not in the directory
		dirfiles = await(file.Readdir(dir, 0));
		REQUIRE(dirfiles.size() == 0);

		// Check that the directory we created is present
		dirfiles = await(file.Readdir("./",0));
		auto iter = std::find(dirfiles.begin(), dirfiles.end(), std::string{ "testdir" });
		REQUIRE(iter != dirfiles.end());

		// Delete the directory
		file.Rmdir(dir);

		// Check that it is no longer present
		dirfiles = await(file.Readdir("./",0));
		iter = std::find(dirfiles.begin(), dirfiles.end(), std::string{ "testdir" });
		REQUIRE(iter == dirfiles.end());


	});

	auto fut = func();

	loop.Run();

	fut.Get();
}