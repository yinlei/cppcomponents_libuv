#pragma once
#ifndef INCLUDE_GUARD_d8301fbc_dfd7_48a4_a3b1_9e74862a74ad
#define INCLUDE_GUARD_d8301fbc_dfd7_48a4_a3b1_9e74862a74ad

#include <cppcomponents/cppcomponents.hpp>
#include <cppcomponents/events.hpp>
#include <cppcomponents/future.hpp>
#include <cppcomponents/channel.hpp>
#include <cppcomponents/loop_executor.hpp>
#include <cppcomponents/buffer.hpp>


// Define our buffer structure
#if defined(__SVR4) && !defined(__unix__)
# define __unix__
#endif

#if defined(__unix__) || defined(__POSIX__) || \
	defined(__APPLE__) || defined(_AIX)

// from uv-unix.h
/* Note: May be cast to struct iovec. See writev(2). */
/*typedef struct {
	char* base;
	size_t len;
} uv_buf_t;
*/

#include <netinet/in.h>

#define CPPCOMPONENTS_LIBUV_ONCE_INIT PTHREAD_ONCE_INIT

namespace cppcomponents_libuv{
	struct Buffer{
		char* base;
		size_t len;
	};

	typedef int FileOsType;
	typedef int SocketOsType;

}
#else
#ifndef NOMINMAX
#define NOMINMAX
#endif

#include <winsock2.h>
#include <ws2tcpip.h>


/**
* It should be possible to cast uv_buf_t[] to WSABUF[]
* see http://msdn.microsoft.com/en-us/library/ms741542(v=vs.85).aspx
*/
/*typedef struct uv_buf_t {
	ULONG len;
	char* base;
} uv_buf_t;*/
namespace cppcomponents_libuv{
	struct Buffer {
		unsigned long len;
		char* base;
	};

	typedef std::uint64_t SocketOsType;
	typedef int FileOsType;


}
#endif
struct addrinfo;

namespace cppcomponents_libuv{
	// Copied from uv.h
	typedef struct {
		long tv_sec;
		long tv_nsec;
	} TimeSpec;


	typedef struct {
		uint64_t st_dev;
		uint64_t st_mode;
		uint64_t st_nlink;
		uint64_t st_uid;
		uint64_t st_gid;
		uint64_t st_rdev;
		uint64_t st_ino;
		uint64_t st_size;
		uint64_t st_blksize;
		uint64_t st_blocks;
		uint64_t st_flags;
		uint64_t st_gen;
		TimeSpec st_atim;
		TimeSpec st_mtim;
		TimeSpec st_ctim;
		TimeSpec st_birthtim;
	} Stat;


}

 namespace cross_compiler_interface{

	 template<>
	 struct cross_conversion<cppcomponents_libuv::Buffer>
		 :public trivial_conversion<cppcomponents_libuv::Buffer>{};
	 template<>
	 struct cross_conversion<cppcomponents_libuv::Buffer*>
		 :public trivial_conversion<cppcomponents_libuv::Buffer*>{};
	 template<>
	 struct cross_conversion<const cppcomponents_libuv::Buffer*>
		 :public trivial_conversion<const cppcomponents_libuv::Buffer*>{};

	 template<>
	 struct cross_conversion<sockaddr>
		 :public trivial_conversion<sockaddr>{};
	 template<>
	 struct cross_conversion<sockaddr*>
		 :public trivial_conversion<sockaddr*>{};
	 template<>
	 struct cross_conversion<const sockaddr*>
		 :public trivial_conversion<const sockaddr*>{};	
	 
	 template<>
	 struct cross_conversion<sockaddr_in6>
		 :public trivial_conversion<sockaddr_in6>{};
	 template<>
	 struct cross_conversion<sockaddr_in6*>
		 :public trivial_conversion<sockaddr_in6*>{};
	 template<>
	 struct cross_conversion<const sockaddr_in6*>
		 :public trivial_conversion<const sockaddr_in6*>{};

	 template<>
	 struct cross_conversion<sockaddr_in>
		 :public trivial_conversion<sockaddr_in>{};
	 template<>
	 struct cross_conversion<sockaddr_in*>
		 :public trivial_conversion<sockaddr_in*>{};
	 template<>
	 struct cross_conversion<const sockaddr_in*>
		 :public trivial_conversion<const sockaddr_in*>{};

	 template<>
	 struct cross_conversion<addrinfo*>
		 :public trivial_conversion<addrinfo*>{};


	 template<>
	 struct cross_conversion<cppcomponents_libuv::TimeSpec>
		 :public trivial_conversion<cppcomponents_libuv::TimeSpec>{};
	 template<>
	 struct cross_conversion<cppcomponents_libuv::TimeSpec*>
		 :public trivial_conversion<cppcomponents_libuv::TimeSpec*>{};
	 template<>
	 struct cross_conversion<const cppcomponents_libuv::TimeSpec*>
		 :public trivial_conversion<const cppcomponents_libuv::TimeSpec*>{};
	 template<>
	 struct cross_conversion<cppcomponents_libuv::Stat>
		 :public trivial_conversion<cppcomponents_libuv::Stat>{};
	 template<>
	 struct cross_conversion<cppcomponents_libuv::Stat*>
		 :public trivial_conversion<cppcomponents_libuv::Stat*>{};
	 template<>
	 struct cross_conversion<const cppcomponents_libuv::Stat*>
		 :public trivial_conversion<const cppcomponents_libuv::Stat*>{};


 }

#include "implementation/errors.hpp"
#include "implementation/constants.hpp"

 namespace cppcomponents{
	 template<>
	 struct uuid_of<cppcomponents_libuv::Buffer>
	 {
		 typedef cppcomponents::uuid<0x032e4f42, 0x8ba7, 0x4cb3, 0xa55e, 0x25dcecbe26a4> uuid_type;
	 
	 };
	 template<>
	 struct uuid_of<sockaddr>
	 {
		 typedef cppcomponents::uuid<0xf283fe4f, 0x50a6, 0x4ec4, 0xa287, 0x015da4711d39> uuid_type;

	 };
	 template<>
	 struct uuid_of<sockaddr_in6>
	 {
		 typedef cppcomponents::uuid<0xc3d8846c, 0x9dac, 0x45b8, 0xbe1d, 0xe4ee8f997f39> uuid_type;

	 };
	 template<>
	 struct uuid_of<sockaddr_in>
	 {
		 typedef cppcomponents::uuid<0xa1d727db, 0x962e, 0x4809, 0x89f6, 0x6536c6435396> uuid_type;

	 };
	 template<>
	 struct uuid_of<addrinfo>
	 {
		 typedef cppcomponents::uuid<0x68392e5e, 0x5a4b, 0x4e71, 0x89db, 0xd335896cd8b7> uuid_type;

	 };


	 template<>
	 struct uuid_of<cppcomponents_libuv::TimeSpec>
	 {
		 typedef cppcomponents::uuid<0x4b6f550d, 0xd170, 0x46a4, 0x9cb5, 0xfaa8f6dc179e> uuid_type;

	 };

	 template<>
	 struct uuid_of<cppcomponents_libuv::Stat>
	 {
		 typedef cppcomponents::uuid<0xb1fa1121, 0xf2ce, 0x4c03, 0x85a8, 0xbd414711ed00> uuid_type;

	 };


 }
namespace cppcomponents_libuv{

	using cppcomponents::use;
	using cppcomponents::define_interface;
	using cppcomponents::cr_string;
	using cppcomponents::object_interfaces;
	using cppcomponents::factory_interface;
	using cppcomponents::static_interfaces;
	using cppcomponents::runtime_class;
	using cppcomponents::use_runtime_class;
	using cppcomponents::implement_runtime_class;




	// All the Interfaces declared

	// Requests

	//struct IRequest;
	//struct IGetAddrinfoRequest;
	//struct IShutdownRequest;
	//struct IWriteRequest;
	//struct IConnectRequest;
	//struct IUdpSendRequest;
	//struct IFsRequest;
	//struct IWorkRequest;


	//// Handles
	//struct ILoop ;
	//struct IHandle ;
	//struct IStream ;
	//struct ITcpStream ;
	//struct IUdpStream ;
	//struct IPipe ;
	//struct ITty ;
	//struct IPoll ;
	//struct ITimer ;
	//struct IPrepare ;
	//struct ICheck ;
	//struct IIdle ;
	//struct IAsync ;
	//struct IProcess ;
	//struct IFsEvent ;
	//struct IFsPoll ;
	//struct ISignal ;


	struct IHandle
		: cppcomponents::define_interface < cppcomponents::uuid <
		0xdeb1580e, 0x08e2, 0x4f67, 0xa03c, 0x90d155bb04be
		>>
	{
		typedef cppcomponents::delegate < void(),
			cppcomponents::uuid<0x5287f549, 0x9b31, 0x4707, 0x93d0, 0xf0ac3fec8b45>
		> CloseCallback;


		int HandleType();
		bool IsActive();
		void CloseRaw(cppcomponents::use<CloseCallback>);
		void Ref();
		void Unref();
		bool HasRef();
		bool IsClosing();
		void* UvHandle();


		CPPCOMPONENTS_CONSTRUCT(IHandle, HandleType, IsActive, CloseRaw, Ref, Unref, HasRef, IsClosing, UvHandle);

		CPPCOMPONENTS_INTERFACE_EXTRAS(IHandle){

			cppcomponents::Future<void> Close(){
				auto p = cppcomponents::make_promise<void>();
				auto f = [p](){
					p.Set();
				};
				this->get_interface().CloseRaw(cppcomponents::make_delegate<CloseCallback>(f));
				return p.QueryInterface < cppcomponents::IFuture<void>>();
			}

		};
	};

	typedef IHandle::CloseCallback CloseCallback;

	// Callbacks
	typedef cppcomponents::delegate < Buffer(use<IHandle> handle, std::ptrdiff_t suggested_size),
		cppcomponents::uuid<0x3298fd84, 0xe097, 0x4fc5, 0x9b28, 0x60e1f5e5d0c8	>
	> AllocCallback;








































	struct IRequest
		: public cppcomponents::define_interface < cppcomponents::uuid < 0xd6d00c3e , 0x5a30 , 0x48c9 , 0x9f48 , 0x9f535bdc4af6	>>
	{
		int RequestType();
		int Cancel();
		void* GetData();
		void SetData(void*);
		void* UvHandle();

		CPPCOMPONENTS_CONSTRUCT(IRequest, RequestType, Cancel,GetData,SetData,UvHandle);
	};


















	struct ILoop
		: cppcomponents::define_interface < cppcomponents::uuid < 0xfc3c5e3c , 0x10af , 0x47a3 , 0x89fc , 0xdaea39cb9d58>>
	{
		struct IWorkRequest
			: public cppcomponents::define_interface < cppcomponents::uuid<0xb2466973, 0xc746, 0x4730, 0x9c7b, 0x944b60607e11>,
			IRequest>
		{
			cppcomponents::use<ILoop> GetLoop();

			CPPCOMPONENTS_CONSTRUCT(IWorkRequest, GetLoop);
		};

		typedef cppcomponents::delegate < void(use<IWorkRequest>),
			cppcomponents::uuid<0x00387da7, 0x2931, 0x4f8f, 0xaa6e, 0x66afb7c0c4a0>
		> WorkCallback;

		typedef cppcomponents::delegate < void(use<IWorkRequest>, int status),
			cppcomponents::uuid<0xf2cd0ccb, 0x3307, 0x438c, 0x8e7b, 0x4b52f563129a>
		> AfterWorkCallback;

		typedef cppcomponents::delegate < void(use<IHandle>),
			cppcomponents::uuid<0x6b443ec5, 0x32ca, 0x4d3d, 0x99e0, 0xb2b1a33c3111>
		> WalkCallback;

		void Run();
		void RunOnce();
		void RunNoWait();

		void Stop();
		void UpdateTime();
		std::uint64_t Now();
		int BackendFd();
		int BackendTimeout();

		void* UvHandle();

		void WalkRaw(cppcomponents::use<WalkCallback>);

		use<IWorkRequest> QueueWorkRaw(cppcomponents::use<WorkCallback>, cppcomponents::use<AfterWorkCallback>);


		CPPCOMPONENTS_CONSTRUCT(ILoop, Run, RunOnce, RunNoWait,
			Stop,UpdateTime,Now,BackendFd, BackendTimeout
			,UvHandle,WalkRaw,QueueWorkRaw);

		CPPCOMPONENTS_INTERFACE_EXTRAS(ILoop){
			template<class F>
			void Walk(F f){
				this->get_interface().WalkRaw(cppcomponents::make_delegate<WalkCallback>(f));
			}
			template<class F>
			cppcomponents::use<cppcomponents::IFuture<void>> QueueWork(F f){
				using namespace cppcomponents;
				auto p = cppcomponents::implement_future_promise<void>::create().QueryInterface<IPromise<void>>();
				auto w = [f](cppcomponents::use<IWorkRequest>){f(); };
				auto after = [p](cppcomponents::use<IWorkRequest>, int status){
					if (status < 0){
						p.SetError(status);
					}
					else{
						p.Set();
					}
				};
				this->get_interface().QueueWorkRaw(cppcomponents::make_delegate<WorkCallback>(w), cppcomponents::make_delegate<AfterWorkCallback>(after));
				return p.QueryInterface<IFuture<void>>();
			}
		};
	};

	typedef ILoop::IWorkRequest IWorkRequest;
	typedef ILoop::WalkCallback WalkCallback;
	typedef ILoop::WorkCallback WorkCallback;
	typedef ILoop::AfterWorkCallback AfterWorkCallback;



	struct ILoopStatics
		: cppcomponents::define_interface < cppcomponents::uuid < 0xd84fa990, 0xccb8, 0x4480, 0x8a3c, 0xb494ef8d79a0>>
	{
		cppcomponents::use<ILoop> DefaultLoop();
		CPPCOMPONENTS_CONSTRUCT(ILoopStatics, DefaultLoop);
	};

	inline std::string LoopId(){ return "cppcomponents_libuv_dll!Loop"; }
	typedef cppcomponents::runtime_class<LoopId, cppcomponents::object_interfaces<ILoop>, cppcomponents::static_interfaces<ILoopStatics>> Loop_t;
	typedef cppcomponents::use_runtime_class<Loop_t> Loop;


	struct ICpuInfo
		: public cppcomponents::define_interface < cppcomponents::uuid < 0x747f0089, 0xea00, 0x4821, 0xa75c, 0xd64760ef98cc	>>
	{
		cppcomponents::cr_string GetModel();
		std::int32_t GetSpeed();
		std::int64_t GetUser();
		std::int64_t GetNice();
		std::int64_t GetSys();
		std::int64_t GetIdle();
		std::int64_t GetIrq();

		CPPCOMPONENTS_CONSTRUCT(ICpuInfo, GetModel, GetSpeed, GetUser, GetNice, GetSys, GetIdle, GetIrq);

	};

	inline std::string CpuInfoId(){ return "cppcomponents_libuv_dll!CpuInfo"; }
	typedef cppcomponents::runtime_class < CpuInfoId, cppcomponents::object_interfaces<ICpuInfo>,
		cppcomponents::factory_interface < cppcomponents::NoConstructorFactoryInterface >>
		CpuInfo_t;


	struct IInterfaceAddress
		: public cppcomponents::define_interface < cppcomponents::uuid < 0x58aef2f1, 0xa1b6, 0x4a14, 0xa417, 0x9f1f95fed845	>>
	{
		cppcomponents::cr_string GetName();
		cppcomponents::cr_string GetPhysAddr();
		bool IsInternal();
		sockaddr_in GetAddress4();
		sockaddr_in6 GetAddress6();
		sockaddr_in GetNetMask4();
		sockaddr_in6 GetNetMask6();

		CPPCOMPONENTS_CONSTRUCT(IInterfaceAddress, GetName, GetPhysAddr, IsInternal, GetAddress4, GetAddress6,
			GetNetMask4, GetNetMask6);
	};
	inline std::string InterfaceAddressId(){ return "cppcomponents_libuv_dll!InterfaceAddress"; }
	typedef cppcomponents::runtime_class < InterfaceAddressId, cppcomponents::object_interfaces<IInterfaceAddress>,
		cppcomponents::factory_interface < cppcomponents::NoConstructorFactoryInterface >>
		InterfaceAddress_t;

	struct IGetAddrinfoRequest
		: public cppcomponents::define_interface < cppcomponents::uuid<0x9c3fbcb4, 0xa35e, 0x4486, 0x9377, 0xedb1262e5f6e>,
		IRequest>
	{
		cppcomponents::use<ILoop> GetLoop();

		CPPCOMPONENTS_CONSTRUCT(IGetAddrinfoRequest, GetLoop);
	};

	typedef cppcomponents::delegate < void (use<IGetAddrinfoRequest>, int status, addrinfo* res),
		cppcomponents::uuid < 0x3249125d, 0x8a0b, 0x488c, 0xbf11, 0x9968f4e8a85d >
	> GetAddrinfoCallback;

	struct IUvStatics
		: cppcomponents::define_interface < cppcomponents::uuid < 0x92979519, 0x8fe7, 0x42cf, 0x8916, 0x6e6e66b46d4a	>>
	{
		int Version();
		cppcomponents::cr_string VersionString();
		cppcomponents::cr_string Strerror(int err);
		cppcomponents::cr_string ErrName(int err);
		std::size_t HandleSize(int type);
		std::size_t ReqSize(int type);
		Buffer BufInit(void* base, std::uint32_t len);
		std::size_t Strlcpy(char* dst, const char* src, std::size_t size);
		std::size_t Strlcat(char* dst, const char* src, std::size_t size);
		int GuessHandle(FileOsType file);

		use<IGetAddrinfoRequest> GetaddrinfoRaw(cppcomponents::use<ILoop>, cppcomponents::use<GetAddrinfoCallback>, cppcomponents::cr_string node,
			cppcomponents::cr_string service, addrinfo* hints);

		void Freeaddrinfo(addrinfo* ai);

		char** SetupArgs(int argc, char** argv);

		std::string GetProcessTitle();
		void SetProcessTitle(cppcomponents::cr_string);
		std::size_t ResidentSetMemory();
		double Uptime();

		std::vector<cppcomponents::use<ICpuInfo>> CpuInfo();
		std::vector<cppcomponents::use<IInterfaceAddress>> InterfaceAddresses();
		std::vector<double> Loadavg();

		sockaddr_in Ip4Addr(cr_string ip, int port);
		sockaddr_in6 Ip6Addr(cr_string ip, int port);

		std::string Ip4Name(sockaddr_in* src);
		std::string Ip6Name(sockaddr_in6* src);

		std::string InetNtop(int af, const void* src);
		void InetPton(int af, cr_string src, void* dst);

		std::string Exepath();
		std::string Cwd();
		void Chdir(cr_string dir);

		std::uint64_t GetFreeMemory();
		std::uint64_t GetTotalMemory();

		std::uint64_t Hrtime();

		void DisableStdioInheritance();

		// No support for dl* use cross_compiler_interface::module


		CPPCOMPONENTS_CONSTRUCT(IUvStatics, Version, VersionString,
			Strerror, ErrName, HandleSize, ReqSize, BufInit, Strlcpy, Strlcat, GuessHandle,
			GetaddrinfoRaw, Freeaddrinfo, SetupArgs, GetProcessTitle, SetProcessTitle, ResidentSetMemory, Uptime,
			CpuInfo, InterfaceAddresses, Loadavg, Ip4Addr, Ip6Addr,
			Ip4Name, Ip6Name, InetNtop, InetPton, Exepath, Cwd, Chdir,
			GetFreeMemory, GetTotalMemory, Hrtime, DisableStdioInheritance

			);


		CPPCOMPONENTS_INTERFACE_EXTRAS(IUvStatics){

			cppcomponents::Future<addrinfo*> Getaddrinfo(cppcomponents::use<ILoop> loop,  cppcomponents::cr_string node,
				cppcomponents::cr_string service, addrinfo* hints){

					auto p = cppcomponents::make_promise<addrinfo*>();
					auto f = [p](use<IGetAddrinfoRequest>, int status, addrinfo* res){
						if (status < 0){
							p.SetError(status);
						}
						else{
							p.Set(res);
						}
					};

					this->get_interface().GetaddrinfoRaw(loop, cppcomponents::make_delegate<GetAddrinfoCallback>(f), node, service, hints);

					return p.QueryInterface < cppcomponents::IFuture<addrinfo*>>();

			}

		};

	};




	inline std::string UvId(){ return "cppcomponents_libuv_dll!Uv"; }

	typedef cppcomponents::runtime_class<UvId, cppcomponents::static_interfaces<IUvStatics>> Uv_t;
	typedef cppcomponents::use_runtime_class<Uv_t> Uv;
	
	struct IStream
		: public cppcomponents::define_interface < cppcomponents::uuid < 
		0x9b7c72d8 , 0xb955 , 0x4163 , 0x9e1f , 0x0c905b60c58f
		>,IHandle>
	{
		struct IWriteRequest
			: public cppcomponents::define_interface < cppcomponents::uuid<0xe3e326d2, 0x49ea, 0x4193, 0x9508, 0x108a95c8a29e>,
			IRequest>
		{
			cppcomponents::use<IStream> GetHandle();
			cppcomponents::use<IStream> GetSendHandle();

			CPPCOMPONENTS_CONSTRUCT(IWriteRequest, GetHandle, GetSendHandle);
		};

		struct IShutdownRequest
			: public cppcomponents::define_interface < cppcomponents::uuid<0x54fdda53, 0xa752, 0x434b, 0x8103, 0xbf35351a3b22>,
			IRequest>
		{
			cppcomponents::use<IStream> GetHandle();

			CPPCOMPONENTS_CONSTRUCT(IShutdownRequest, GetHandle);
		};

		typedef cppcomponents::delegate < void(use<IStream> stream, std::ptrdiff_t,  cppcomponents::use<cppcomponents::IBuffer>),
			cppcomponents::uuid<0x38df861d, 0x421b, 0x43d1, 0xb081, 0x7d2ad030c44c		>
		> ReadCallback;

		typedef cppcomponents::delegate < void(use<IStream> pipe, std::ptrdiff_t nread, cppcomponents::use<cppcomponents::IBuffer>,
			int pending),
			cppcomponents::uuid<0xd4efdca8, 0xc398, 0x465a, 0x8812, 0x653250b6cdb4		>
		> Read2Callback;

		typedef cppcomponents::delegate < void(use<IWriteRequest>, int status),
			cppcomponents::uuid<0x1c150cb2, 0xde88, 0x46cf, 0xbfad, 0xeb6ede7611ed>
		> WriteCallback;
		typedef cppcomponents::delegate < void(use<IShutdownRequest>, int),
			cppcomponents::uuid<0x121276b6, 0x4d00, 0x4db3, 0xb0e2, 0xbf761a031162>
		> ShutdownCallback;


		typedef cppcomponents::delegate < void(use<IStream>, int),
			cppcomponents::uuid<0x2965d620, 0xac78, 0x4f07, 0xb10b, 0x748401d69656>
		> ConnectionCallback;



		use<IShutdownRequest> ShutdownRaw(cppcomponents::use<ShutdownCallback>);
		void ListenRaw(int backlog, cppcomponents::use<ConnectionCallback>);
		void Accept(use<IStream> client);

		void ReadStartRaw(cppcomponents::use<ReadCallback>);
		void ReadStop();
		void Read2StartRaw(cppcomponents::use<Read2Callback>);
		use<IWriteRequest> WriteRaw(cppcomponents_libuv::Buffer* bufs, int bufcnt, cppcomponents::use<WriteCallback>);
		use<IWriteRequest> Write2Raw(cppcomponents_libuv::Buffer* bufs, int bufcnt, cppcomponents::use <IStream>, cppcomponents::use<WriteCallback>);
		bool IsReadable();
		bool IsWritable();
		void SetBlocking(bool blocking);




		CPPCOMPONENTS_CONSTRUCT(IStream, ShutdownRaw,ListenRaw,Accept,ReadStartRaw,ReadStop,Read2StartRaw,WriteRaw,
			Write2Raw,IsReadable,IsWritable,SetBlocking);

		CPPCOMPONENTS_INTERFACE_EXTRAS(IStream){
			
			cppcomponents::use<cppcomponents::IFuture<int>> Shutdown(){
				auto p = cppcomponents::make_promise<int>();

				auto f = [p](use<IShutdownRequest>, int s){
					p.Set(s);
				};
				this->get_interface().ShutdownRaw(cppcomponents::make_delegate<ShutdownCallback>(f));

				return p.QueryInterface<cppcomponents::IFuture<int>>();
			}

			template<class F>
			void Listen(int backlog, F f){
				this->get_interface().ListenRaw(backlog, cppcomponents::make_delegate<ConnectionCallback>(f));

			}

			cppcomponents::Channel<cppcomponents::use<IStream>> ListenWithChannel(int backlog){
				typedef cppcomponents::use<IStream> c_t;
				auto chan = cppcomponents::make_channel < c_t>();


				auto f = [chan](use<IStream> stream, int status){
					if (status >= 0){
						chan.Write(stream);
					}
					else{
						chan.WriteError(status);
					}
				};


				Listen(backlog,f);

				return chan;
			}
			template<class F>
			void ReadStart(F f){
				this->get_interface().ReadStartRaw(cppcomponents::make_delegate<ReadCallback>(f));
			}

			cppcomponents::Channel<cppcomponents::use<cppcomponents::IBuffer>> ReadStartWithChannel(){
				typedef cppcomponents::use<cppcomponents::IBuffer> c_t;
				auto chan = cppcomponents::make_channel < c_t>();


				auto f = [chan](use<IStream> stream, std::ptrdiff_t nread, cppcomponents::use<cppcomponents::IBuffer> buf){
					if (nread >= 0){
						chan.Write(buf);
					}
					else{
						chan.WriteError(nread);
					}
				};


				ReadStart(f);

				return chan;
			}
			

			template<class F>
			void Read2Start(F f){
				this->get_interface().Read2StartRaw(cppcomponents::make_delegate<ReadCallback>(f));
			}



			cppcomponents::use<cppcomponents::IFuture<int>> Write(Buffer* bufs, int bufcnt){
				auto p = cppcomponents::make_promise<int>();
				auto func = [p](cppcomponents::use<IWriteRequest>, int status){
					if (status < 0){
						p.SetError(status);
					}
					else{
						p.Set(status);
					}
				};
				this->get_interface().WriteRaw(bufs,bufcnt,cppcomponents::make_delegate<WriteCallback>(func));
				return p.QueryInterface<cppcomponents::IFuture<int>>();
			}

			template<std::size_t N>
			cppcomponents::use<cppcomponents::IFuture<int>> Write(const char (&ar)[N]){
				Buffer b;
				b.base = const_cast<char*>(&ar[0]);
				b.len = N;
				
				return Write(&b, 1);
			}



			template<std::size_t N>
			cppcomponents::use<cppcomponents::IFuture<int>> Write(Buffer (&ar)[N]){

				return Write(&ar[0], N);
			}

			cppcomponents::use<cppcomponents::IFuture<int>> Write(const std::vector<Buffer>& bufs){

				return Write(const_cast<char*>(&bufs.at(0)), bufs.size());
			}


			cppcomponents::use<cppcomponents::IFuture<int>> Write(const char* data, std::size_t len){
				Buffer b;
				b.base = const_cast<char*>(data);
				b.len = len;

				return Write(&b, 1);
			}

			cppcomponents::use<cppcomponents::IFuture<int>> Write(const std::vector<char>& v){
				return Write(&v.at(0),v.size());
			}

			cppcomponents::use<cppcomponents::IFuture<int>> Write(const std::string& s){
				return Write(&s.at(0), s.size());
			}

			cppcomponents::use<cppcomponents::IFuture<int>> Write(cppcomponents::cr_string s){
				return Write(&s.at(0), s.size());
			}



		};

	};

	typedef IStream::ReadCallback ReadCallback;
	typedef IStream::Read2Callback Read2Callback;
	typedef IStream::WriteCallback WriteCallback;
	typedef IStream::ConnectionCallback ConnectionCallback;
	typedef IStream::ShutdownCallback ShutdownCallback;
	typedef IStream::IWriteRequest IWriteRequest;
	typedef IStream::IShutdownRequest IShutdownRequest;

	struct ITcpStream
		: public cppcomponents::define_interface < cppcomponents::uuid <
		0x7e57d378 , 0xa97c , 0x463d , 0xb153 , 0xd7c414ab4c59
		>,IStream>
	{
		struct IConnectRequest
			: public cppcomponents::define_interface < cppcomponents::uuid<0x29c0c28e, 0x5a17, 0x433a, 0xa06a, 0x1af0a2e98558>,
			IRequest>
		{
			cppcomponents::use<IStream> GetHandle();

			CPPCOMPONENTS_CONSTRUCT(IConnectRequest, GetHandle);
		};

		typedef cppcomponents::delegate < void(use<IConnectRequest>, int),
			cppcomponents::uuid<0x51a43254, 0x1c9b, 0x462e, 0xacc3, 0xecb908249e95>
		> ConnectCallback;

		void Open(SocketOsType sock);
		void NoDelay(bool enable);
		void KeepAlive(bool enable, std::uint32_t delay);
		void SimultaneousAccepts(bool enable);
		void Bind(sockaddr_in);
		void Bind6(sockaddr_in6);
		void Getsockname(sockaddr* name, int* namelen);
		void Getpeername(sockaddr* name, int* namelen);
		use<IConnectRequest> ConnectRaw(sockaddr_in address, cppcomponents::use<ConnectCallback>);
		use<IConnectRequest> Connect6Raw(sockaddr_in6 address, cppcomponents::use<ConnectCallback>);

		CPPCOMPONENTS_CONSTRUCT(ITcpStream, Open,NoDelay,KeepAlive,SimultaneousAccepts,
			Bind,Bind6,Getsockname,Getpeername,ConnectRaw,Connect6Raw);

		CPPCOMPONENTS_INTERFACE_EXTRAS(ITcpStream){
			cppcomponents::Future<int> Connect(sockaddr_in address){
				auto p = cppcomponents::make_promise<int>();
				auto f = [p](use<IConnectRequest>, int result){
					if (result < 0){
						p.SetError(result);
					}
					else{
						p.Set(result);
					}
				};

				this->get_interface().ConnectRaw(address, cppcomponents::make_delegate<ConnectCallback>(f));

				return p.QueryInterface<cppcomponents::IFuture<int>>();
	
			}
			cppcomponents::Future<int> Connect(sockaddr_in6 address){
				auto p = cppcomponents::make_promise<int>();
				auto f = [p](use<IConnectRequest>, int result){
					if (result < 0){
						p.SetError(result);
					}
					else{
						p.Set(result);
					}
				};

				this->get_interface().Connect6Raw(address, cppcomponents::make_delegate<ConnectCallback>(f));

				return p.QueryInterface<cppcomponents::IFuture<int>>();
	
			}

		};
	};

	typedef ITcpStream::ConnectCallback ConnectCallback;
	typedef ITcpStream::IConnectRequest IConnectRequest;

	struct ILoopInitFactory
		: public cppcomponents::define_interface <
		cppcomponents::uuid
		<0x83be8a93 , 0x5883 , 0x4961 , 0xb885 , 0xab20a4b93919>>
	{
		cppcomponents::use<cppcomponents::InterfaceUnknown> Init(cppcomponents::use<ILoop>);

		CPPCOMPONENTS_CONSTRUCT(ILoopInitFactory, Init);
	};
	inline std::string TcpStreamId(){return "cppcomponents_libuv_dll!TcpStream";}
	typedef runtime_class<TcpStreamId, object_interfaces<ITcpStream>, factory_interface<ILoopInitFactory>> TcpStream_t;
	typedef use_runtime_class<TcpStream_t> TcpStream;
	

	struct IUdpStream
		: public cppcomponents::define_interface < cppcomponents::uuid <
		0x2c4a1e5e , 0x4362 , 0x45db , 0xb8d6 , 0xac71c6810066
		> , IStream >
	{
		struct IUdpSendRequest
			: public cppcomponents::define_interface < cppcomponents::uuid<0xc838dab9, 0x8815, 0x4592, 0x84f4, 0x3574ea72db0d>,
			IRequest>
		{
			cppcomponents::use<IStream> GetHandle();

			CPPCOMPONENTS_CONSTRUCT(IUdpSendRequest, GetHandle);
		};

		typedef cppcomponents::delegate < void(use<IUdpSendRequest>, int status),
			cppcomponents::uuid<0x5f2d1356, 0x7025, 0x4459, 0xb843, 0x9610a57f79be>
		> UdpSendCallback;

		typedef cppcomponents::delegate < void (use<IUdpStream>, std::ptrdiff_t nread,
			Buffer buf, const sockaddr* addr, unsigned int flags),
			cppcomponents::uuid<0x62a0f712, 0x99f5, 0x4a09, 0x9d00, 0x2ec1b2dd6cea>
		> UdpRecvCallback;


		void Open(SocketOsType sock);
		void Bind(sockaddr_in in, std::uint32_t flags);
		void Bind6(sockaddr_in6 in, std::uint32_t flags);
		void GetSockname(sockaddr* name, int* namelen);
		void SetMembership(cppcomponents::cr_string multicast_addr, cppcomponents::cr_string interface_addr,
			std::uint32_t membership);
		void SetMulticastLoop(bool on);
		void SetMulticastTtl(std::int32_t ttl);
		void SetBroadcast(bool on);
		void SetTtl(std::int32_t ttl);
		use<IUdpSendRequest> Send(Buffer* bufs, int buffcnt, sockaddr_in addr,
			cppcomponents::use<UdpSendCallback> send_cb);
		use<IUdpSendRequest> Send6(Buffer* bufs, int buffcnt, sockaddr_in6 addr,
			cppcomponents::use<UdpSendCallback> send_cb);

		void RecvStart(cppcomponents::use<UdpRecvCallback>);
		void RecvStop();

		CPPCOMPONENTS_CONSTRUCT(IUdpStream, Open,Bind,Bind6,GetSockname,SetMembership,
			SetMulticastLoop,SetMulticastTtl,SetBroadcast,SetTtl,Send,Send6,RecvStart,RecvStop);
	};

	typedef IUdpStream::IUdpSendRequest IUdpSendRequest;
	typedef IUdpStream::UdpSendCallback UdpSendCallback;
	typedef IUdpStream::UdpRecvCallback UdpRecvCallback;

	inline std::string UdpStreamId(){ return "cppcomponents_libuv_dll!UdpStream"; }
	typedef runtime_class<UdpStreamId, object_interfaces<IUdpStream>, factory_interface<ILoopInitFactory>> UdpStream_t;
	typedef use_runtime_class<UdpStream_t> UdpStream;


	struct ITty
		: public cppcomponents::define_interface <
		cppcomponents::uuid<0x87fa2ac3 , 0x2119 , 0x4aa7 , 0x98d1 , 0xf7bb86e0ae5e		>,
		IStream > 
	{
		void SetMode(int mode);
		std::pair<int,int> GetWinsize();

		CPPCOMPONENTS_CONSTRUCT(ITty, SetMode, GetWinsize);
		
	};

	struct ITtyFactory
		: public cppcomponents::define_interface <
		cppcomponents::uuid
		< 0xc8f22d60, 0xefa2, 0x4d63, 0xa6fc, 0x66d705f77352 >>
	{
		cppcomponents::use<cppcomponents::InterfaceUnknown> Init(cppcomponents::use<ILoop>,FileOsType fd, bool readable);


		CPPCOMPONENTS_CONSTRUCT(ITtyFactory, Init);
	};

	struct ITtyStatics
		: public cppcomponents::define_interface <
		cppcomponents::uuid < 0x3fe4f6da, 0xd38d, 0x46cb, 0x867c, 0x4e4537cb0be0 >>
	{
		void ResetMode();

		CPPCOMPONENTS_CONSTRUCT(ITtyStatics, ResetMode);
	};

	inline std::string TtyId(){ return "cppcomponents_libuv_dll!Tty"; }
	typedef runtime_class<TtyId, object_interfaces<ITty>, factory_interface<ITtyFactory>,
	static_interfaces<ITtyStatics>> Tty_t;
	typedef use_runtime_class<Tty_t> Tty;

	struct IPipe
		: public cppcomponents::define_interface <
		cppcomponents::uuid<0xce484587 , 0x7aa3 , 0x477c , 0x9ad8 , 0xd86ca293babf>,
		IStream >
	{
		void Open(FileOsType file);
		void Bind(cppcomponents::cr_string name);
		use<IConnectRequest> Connect(cppcomponents::cr_string name, cppcomponents::use<ConnectCallback> cb);
		void PendingInstances(int count);

		CPPCOMPONENTS_CONSTRUCT(IPipe, Open, Bind, Connect, PendingInstances);

	};

	struct IPipeFactory
		: public cppcomponents::define_interface <
		cppcomponents::uuid
		< 0xa8175c7e , 0x65a4 , 0x4659 , 0x8648 , 0x64ff00e2fc4b	>>
	{
		cppcomponents::use<cppcomponents::InterfaceUnknown> Init(cppcomponents::use<ILoop>, bool ipc);


		CPPCOMPONENTS_CONSTRUCT(IPipeFactory, Init);
	};
	inline std::string PipeId(){ return "cppcomponents_libuv_dll!Pipe"; }
	typedef runtime_class<PipeId, object_interfaces<IPipe>, factory_interface<IPipeFactory>> Pipe_t;
	typedef use_runtime_class<Pipe_t> Pipe;



	struct IPoll
		: public cppcomponents::define_interface <
		cppcomponents::uuid<0xa7f582ac , 0x8b78 , 0x4988 , 0xad12 , 0x7074bbde7e27>,
		IHandle >
	{
		typedef cppcomponents::delegate < void(use<IPoll>, int status, int events),
			cppcomponents::uuid<0x1679860e, 0x3e67, 0x4b1b, 0x8791, 0x18080f1df647>
		> PollCallback;

		void Start(int events, cppcomponents::use<PollCallback>);
		void Stop();

		CPPCOMPONENTS_CONSTRUCT(IPoll, Start,Stop);

	};

	typedef IPoll::PollCallback PollCallback;

	struct IPollFactory
		: public cppcomponents::define_interface <
		cppcomponents::uuid
		< 0x7f35a833 , 0xf555 , 0x4582 , 0x8e02 , 0x080a6c36f528		>>
	{
		cppcomponents::use<cppcomponents::InterfaceUnknown> Init(cppcomponents::use<ILoop>, std::int64_t fileorsocket, bool isfile);


		CPPCOMPONENTS_CONSTRUCT(IPollFactory, Init);
	};

	inline std::string PollId(){ return "cppcomponents_libuv_dll!Poll"; }
	typedef runtime_class<PollId, object_interfaces<IPoll>, factory_interface<IPollFactory>> Poll_t;
	typedef use_runtime_class<Poll_t> Poll;

	struct IPrepare
		: public cppcomponents::define_interface <
		cppcomponents::uuid<0xc15bdb50 , 0x4fc6 , 0x4224 , 0x984d , 0x4a9e57f3d7ee		>,
		IHandle >
	{
		typedef cppcomponents::delegate < void(use<IPrepare>, int status),
			cppcomponents::uuid<0x66854dad, 0x0408, 0x4c4e, 0xafcd, 0x5a2fe7366914>
		> PrepareCallback;

		void StartRaw(cppcomponents::use<PrepareCallback>);
		void Stop();

		CPPCOMPONENTS_CONSTRUCT(IPrepare, StartRaw, Stop);

		CPPCOMPONENTS_INTERFACE_EXTRAS(IPrepare){
			template<class F>
			void Start(F f){
				this->get_interface().StartRaw(cppcomponents::make_delegate<PrepareCallback>(f));
			}
		};
	};

	typedef IPrepare::PrepareCallback PrepareCallback;

	inline std::string PrepareId(){ return "cppcomponents_libuv_dll!Prepare"; }
	typedef runtime_class < PrepareId, object_interfaces<IPrepare>, factory_interface<ILoopInitFactory>> Prepare_t;
	typedef use_runtime_class<Prepare_t> Prepare;

	
	struct ICheck
		: public cppcomponents::define_interface <
		cppcomponents::uuid<0x313b4d56 , 0x1def , 0x431d , 0x84fb , 0x48556b725e20		>,
		IHandle >
	{
		typedef cppcomponents::delegate < void(use<ICheck>, int status),
			cppcomponents::uuid<0x5817e0e6, 0x31c8, 0x40ab, 0xbce5, 0x6913db56a285>
		> CheckCallback;

		void Start(cppcomponents::use<CheckCallback>);
		void Stop();

		CPPCOMPONENTS_CONSTRUCT(ICheck, Start, Stop);
	};

	typedef ICheck::CheckCallback CheckCallback;

	inline std::string CheckId(){ return "cppcomponents_libuv_dll!Check"; }
	typedef runtime_class<CheckId, object_interfaces<ICheck>, factory_interface<ILoopInitFactory>> Check_t;
	typedef use_runtime_class<Check_t> Check;


	struct IIdle
		: public cppcomponents::define_interface <
		cppcomponents::uuid<0xdc2333a3 , 0xa2c8 , 0x47c4 , 0xbfde , 0xee062553c8df>,
		IHandle >
	{
		typedef cppcomponents::delegate < void(use<IIdle>, int status),
			cppcomponents::uuid<0x05727499, 0xcc1d, 0x4170, 0xa88c, 0xe31f8d014778>
		> IdleCallback;

		void Start(cppcomponents::use<IdleCallback>);
		void Stop();

		CPPCOMPONENTS_CONSTRUCT(IIdle, Start, Stop);
	};	

	typedef IIdle::IdleCallback IdleCallback;

	inline std::string IdleId(){ return "cppcomponents_libuv_dll!Idle"; }
	typedef runtime_class<IdleId, object_interfaces<IIdle>, factory_interface<ILoopInitFactory>> Idle_t;
	typedef use_runtime_class<Idle_t> Idle;

	struct IAsync
		: public cppcomponents::define_interface <
		cppcomponents::uuid<0x5def2371 , 0x0da2 , 0x40de,0x88c4 , 0x1d7aeee7ec4c>,
		IHandle >
	{
		void Send();

		CPPCOMPONENTS_CONSTRUCT(IAsync,Send);
	};

	typedef cppcomponents::delegate < void(use<IAsync>, int status),
		cppcomponents::uuid<0x5259a184, 0x0903, 0x4694, 0xbb4c, 0xa83f241b10da>
	> AsyncCallback;

	struct IAsyncFactory
		: public cppcomponents::define_interface <
		cppcomponents::uuid <0x2d5db39d , 0x52df , 0x4900 , 0xa60f , 0x48c3fcc8b154	> >
	{
		cppcomponents::use<cppcomponents::InterfaceUnknown> Init(cppcomponents::use<ILoop>, cppcomponents::use<AsyncCallback>);

		CPPCOMPONENTS_CONSTRUCT(IAsyncFactory, Init);


		CPPCOMPONENTS_INTERFACE_EXTRAS(IAsyncFactory){

			template<class F>
			cppcomponents::use<cppcomponents::InterfaceUnknown> TemplatedConstructor(cppcomponents::use<ILoop> loop,F f){
				return this->get_interface().Init(loop, cppcomponents::make_delegate<AsyncCallback>(f));
			}

		};
	};



	inline std::string AsyncId(){ return "cppcomponents_libuv_dll!Async"; }
	typedef runtime_class<AsyncId, object_interfaces<IAsync>, factory_interface<IAsyncFactory>> Async_t;
	typedef use_runtime_class<Async_t> Async;


	struct ITimer
		: public cppcomponents::define_interface <
		cppcomponents::uuid<0x5f941871 , 0x8e16 , 0x4c21 , 0xbec6 , 0x33ee71c66afb>,
		IHandle >
	{
		typedef cppcomponents::delegate < void(use<ITimer>, int status),
			cppcomponents::uuid<0xccecc946, 0x1bcd, 0x48c8, 0x818a, 0xbd90445eee11	>
		> TimerCallback;

		void StartRaw(cppcomponents::use<TimerCallback>,std::uint64_t timeout, std::uint64_t repeat);
		void Stop();
		void Again();
		void SetRepeat(std::uint64_t repeat);
		std::uint64_t GetRepeat();

		CPPCOMPONENTS_CONSTRUCT(ITimer,StartRaw,Stop,Again,SetRepeat,GetRepeat);

		CPPCOMPONENTS_INTERFACE_EXTRAS(ITimer){

			template<class F>
			void Start(F f, std::uint64_t timeout, std::uint64_t repeat){
				this->get_interface().StartRaw(cppcomponents::make_delegate<TimerCallback>(f), timeout, repeat);
			}
		};

	};

	typedef ITimer::TimerCallback TimerCallback;

	struct ITimerFactory
		: public cppcomponents::define_interface <
		cppcomponents::uuid <0x52b4032d , 0x2898 , 0x4a5d , 0x944c , 0x9826fa0dddeb		> >
	{
		cppcomponents::use<cppcomponents::InterfaceUnknown> Init(cppcomponents::use<ILoop>);

		CPPCOMPONENTS_CONSTRUCT(ITimerFactory, Init);
	};
	inline std::string TimerId(){ return "cppcomponents_libuv_dll!Timer"; }
	typedef runtime_class<TimerId, object_interfaces<ITimer>, factory_interface<ITimerFactory>> Timer_t;
	typedef use_runtime_class<Timer_t> Timer;





	struct IStdioContainer
		: public cppcomponents::define_interface <
		cppcomponents::uuid < 0x6afae11e, 0x9c4c, 0x449a, 0xab0f, 0xfa14f085464f> >
	{
		int GetFlags();
		void SetFlags(int flags);
		bool IsStream();
		void SetStream(cppcomponents::use<IStream>);
		cppcomponents::use<IStream> GetStream();
		void SetFd(FileOsType fd);
		FileOsType GetFd();

		CPPCOMPONENTS_CONSTRUCT(IStdioContainer, GetFlags, SetFlags, IsStream, SetStream, GetStream, SetFd, GetFd);


	};
	inline std::string StdioContainerId(){ return "cppcomponents_libuv_dll!StdioContainer"; }
	typedef runtime_class<StdioContainerId, object_interfaces<IStdioContainer>> StdioContainer_t;
	typedef use_runtime_class<StdioContainer_t> StdioContainer;




	struct IProcess 
		:public cppcomponents::define_interface < 
		cppcomponents::uuid<0xee9c7f5b , 0x3be6 , 0x4a40 , 0xa689 , 0xa4bd7bbc4f4d	>,
		IHandle>
	{


		void Kill(int signum);
		int GetPid();
		CPPCOMPONENTS_CONSTRUCT(IProcess, Kill,GetPid);
	};


	typedef cppcomponents::delegate < void(use<IProcess>, int64_t status, int term_signal),
		cppcomponents::uuid<0xa585d683, 0x22eb, 0x453d, 0xbcc4, 0x79d4c328afb1>
	> ExitCallback;

	struct IProcessOptions
		: public cppcomponents::define_interface < cppcomponents::uuid < 0x18b90130, 0x2ea2, 0x4c21, 0x934b, 0xf79cf31c7242	>>
	{
		void SetExitCallback(cppcomponents::use<ExitCallback>);
		cppcomponents::use<ExitCallback> GetExitCallback();

		void SetFile(cppcomponents::cr_string file);
		std::string GetFile();

		void SetArgs(std::vector<cppcomponents::cr_string> args);
		std::vector<cppcomponents::cr_string> GetArgs();

		void SetEnv(std::vector<cppcomponents::cr_string> args);
		std::vector<cppcomponents::cr_string> GetEnv();

		void SetCwd(cppcomponents::cr_string file);
		std::string GetCwd();

		unsigned int GetFlags();
		void SetFlags(unsigned int flags);

		void SetStdio(std::vector < cppcomponents::use < IStdioContainer >> );
		std::vector<cppcomponents::use<IStdioContainer>> GetStdio();

		void SetUid(unsigned char);
		unsigned char GetUid();

		void SetGid(unsigned char);
		unsigned char GetGid();


		CPPCOMPONENTS_CONSTRUCT(IProcessOptions, SetExitCallback, GetExitCallback, SetFile, GetFile,
			SetArgs, GetArgs, SetEnv, GetEnv, SetCwd, GetCwd, GetFlags, SetFlags, SetStdio, GetStdio, SetUid, GetUid,
			SetGid, GetGid);

	};
	inline std::string ProcessOptionsId(){ return "cppcomponents_libuv_dll!ProcessOptions"; }
	typedef runtime_class<ProcessOptionsId, object_interfaces<IProcessOptions>> ProcessOptions_t;
	typedef use_runtime_class<ProcessOptions_t> ProcessOptions;

	struct IProcessFactory
		: public cppcomponents::define_interface<
		cppcomponents::uuid<0xff1b1982, 0x6bd6, 0x4096, 0xaf0d, 0xf6488421cc64	> >
	{
		cppcomponents::use<cppcomponents::InterfaceUnknown> Spawn(cppcomponents::use<ILoop>, cppcomponents::use<IProcessOptions>);

		CPPCOMPONENTS_CONSTRUCT(IProcessFactory, Spawn);
	};
	struct IProcessStatics
		: public cppcomponents::define_interface<
		cppcomponents::uuid<0x66fdeeba , 0x6b9f , 0x4003 , 0x8fc1 , 0x8192d21488cf	> >
	{
		void KillProcess(int pid, int signum);

		CPPCOMPONENTS_CONSTRUCT(IProcessStatics, KillProcess);
	};

	inline std::string ProcessId(){ return "cppcomponents_libuv_dll!Process"; }
	typedef runtime_class<ProcessId, object_interfaces<IProcess>, factory_interface<IProcessFactory>,static_interfaces<IProcessStatics>> Process_t;
	typedef use_runtime_class<Process_t> Process;



	struct IFsRequest
		: public cppcomponents::define_interface < cppcomponents::uuid<0x50d9617d, 0xf3e2, 0x4c2a, 0x909f, 0x65c810fa3340>,
		IRequest>
	{
		void Cleanup();
		cppcomponents::use<ILoop> GetLoop();
		std::ptrdiff_t GetResult();
		void* GetPtr();
		cppcomponents::cr_string GetPath();
		Stat GetStatBuf();


		CPPCOMPONENTS_CONSTRUCT(IFsRequest, Cleanup, GetLoop, GetResult, GetPtr, GetPath, GetStatBuf);
	};

	typedef cppcomponents::delegate < void(use<IFsRequest>),
		cppcomponents::uuid<0x51cc28e9, 0xb06d, 0x49e9, 0x85c4, 0x008a37780ea9>
	> FsCallback;





	struct IFsStatics
		: public cppcomponents::define_interface <
		cppcomponents::uuid<0x96340307, 0x442f, 0x4327, 0x8fd0, 0xcbb71d95bf8a>
		>
	{
		use<IFsRequest> Close(use<ILoop>, FileOsType, use<FsCallback>);

		use<IFsRequest> Open(use<ILoop>, cr_string, int flags,
			int mode, use<FsCallback>);

		use<IFsRequest> Read(use<ILoop>, FileOsType file, void* buf,
			std::size_t length, std::int64_t offset, use<FsCallback>);

		use<IFsRequest> Unlink(use<ILoop>, cr_string path, use<FsCallback>);

		use<IFsRequest> Write(use<ILoop>, FileOsType file, const void* buf,
			std::size_t length, std::int64_t offset, use<FsCallback>);

		use<IFsRequest> Mkdir(use<ILoop>, cr_string path, int mode, use<FsCallback>);
		use<IFsRequest> Rmdir(use<ILoop>, cr_string, use<FsCallback>);

		use<IFsRequest> Readdir( use<ILoop>, cr_string path, int flags, use<FsCallback>);
		use<IFsRequest> Stat(use<ILoop>, cr_string path, use<FsCallback>);
		use<IFsRequest> Fstat(use<ILoop>, FileOsType file, use<FsCallback>);
		use<IFsRequest> Rename(use<ILoop>, cr_string path,cr_string new_path, use<FsCallback>);
		use<IFsRequest> Fsync(use<ILoop>, FileOsType file, use<FsCallback>);
		use<IFsRequest> Fdatasync(use<ILoop>, FileOsType file, use<FsCallback>);
		use<IFsRequest> Ftruncate(use<ILoop>, FileOsType file, 
			std::int64_t offset, use<FsCallback>);
		use<IFsRequest> Sendfile(use<ILoop>, FileOsType file_out, FileOsType file_in,
			std::int64_t in_offset, std::size_t length, use<FsCallback>);
		use<IFsRequest> Chmod(use<ILoop>, cr_string path,
			int mode, use<FsCallback>);
		use<IFsRequest> Utime(use<ILoop>, cr_string path, double atime,
			double mtime, use<FsCallback>);
		use<IFsRequest> Futime(use<ILoop>, FileOsType file, double atime,
			double mtime, use<FsCallback>);
		use<IFsRequest> Lstat(use<ILoop>, cr_string path, use<FsCallback>);
		use<IFsRequest> Link(use<ILoop>, cr_string path, cr_string new_path,
			use<FsCallback>);

		use<IFsRequest> Symlink(use<ILoop>, cr_string path,
			cr_string new_path, int flags, use<FsCallback>);
		use<IFsRequest> Readlink(use<ILoop>, cr_string path,
			use<FsCallback>);

		use<IFsRequest> Fchmod(use<ILoop>, FileOsType file,
			int mode, use<FsCallback>);

		use<IFsRequest> Chown(use<ILoop>, cr_string path, unsigned char uid,
			unsigned char gid, use<FsCallback>);

		use<IFsRequest> Fchown(use<ILoop>, FileOsType, unsigned char uid,
			unsigned char gid, use<FsCallback>);


		CPPCOMPONENTS_CONSTRUCT(IFsStatics,
			Close, Open, Read, Unlink, Write, Mkdir, Rmdir, Readdir, Stat, Fstat,
			Rename, Fsync, Fdatasync, Ftruncate, Sendfile, Chmod, Utime, Futime,
			Lstat, Link, Symlink, Readlink, Fchmod, Chown, Fchown);


	};

	inline std::string FsId(){ return "cppcomponents_libuv_dll!Fs"; }
	typedef runtime_class<FsId, static_interfaces<IFsStatics>> Fs_t;
	typedef use_runtime_class<Fs_t> Fs;


	struct IFsPoll
		: public cppcomponents::define_interface <
		cppcomponents::uuid < 0xff330521, 0x0c3e, 0x4c7b, 0x85fd, 0x7cfef3e71cb4 >>
	{
		typedef cppcomponents::delegate < void(use<IFsPoll>,
			int status, const Stat* prev, const Stat* curr),
			cppcomponents::uuid<0xb64e98a1, 0xc2a9, 0x4e5f, 0x9bd9, 0x93d0b2913f97>
		> FsPollCallback;

		void Start(use<FsPollCallback>, cr_string path, unsigned int msinterval);
		void Stop();
		CPPCOMPONENTS_CONSTRUCT(IFsPoll, Start, Stop);
	};

	typedef IFsPoll::FsPollCallback FsPollCallback;

	struct IFsPollFactory
		: public cppcomponents::define_interface <
		cppcomponents::uuid < 0x3facf4bd, 0xb287, 0x4521, 0xa9ab, 0x7e79c1df9da8 >>
	{
		use<cppcomponents::InterfaceUnknown> Init(use<ILoop>);

		CPPCOMPONENTS_CONSTRUCT(IFsPollFactory, Init);
	};

	inline std::string FsPollId(){ return "cppcomponents_libuv_dll!FsPoll"; }
	typedef runtime_class<FsPollId, object_interfaces<IFsPoll>, factory_interface<IFsPollFactory>> FsPoll_t;
	typedef use_runtime_class<FsPoll_t> FsPoll;



	struct ISignal
		: public cppcomponents::define_interface <
		cppcomponents::uuid < 0xce633c27, 0xa8cb, 0x4752, 0xa7b9, 0x119924d606f0 >>
	{
		typedef cppcomponents::delegate < void(use<ISignal>, int signum),
			cppcomponents::uuid<0x320b624c, 0xa2c7, 0x4039, 0xb66e, 0xc7dd27b28a1c>
		> SignalCallback;


		void Start(use<SignalCallback>, int signum );
		void Stop();
		CPPCOMPONENTS_CONSTRUCT(ISignal, Start, Stop);
	};

	typedef ISignal::SignalCallback SignalCallback;

	struct ISignalFactory
		: public cppcomponents::define_interface <
		cppcomponents::uuid < 0x6725ccae, 0x6038, 0x4c07, 0xabe2, 0x710e674b1a06 >>
	{
		use<cppcomponents::InterfaceUnknown> Init(use<ILoop>);

		CPPCOMPONENTS_CONSTRUCT(ISignalFactory, Init);
	}; 

	inline std::string SignalId(){ return "cppcomponents_libuv_dll!Signal"; }
	typedef runtime_class<SignalId, object_interfaces<ISignal>, factory_interface<ISignalFactory>> Signal_t;
	typedef use_runtime_class<Signal_t> Signal;


	struct IFsEvent
		: public cppcomponents::define_interface <
		cppcomponents::uuid<0xcd45427c, 0xed02, 0x408a, 0x83ae, 0xa2848df6b027>
		, IHandle >
	{
		typedef cppcomponents::delegate < void(use<IFsEvent>, cr_string filename,
			int events, int status),
			cppcomponents::uuid<0x42ea1b10, 0x261c, 0x4478, 0x89bb, 0x5203b1ff344a>
		> FsEventCallback;

		CPPCOMPONENTS_CONSTRUCT_NO_METHODS(IFsEvent);
	};

	typedef IFsEvent::FsEventCallback FsEventCallback;

	struct IFsEventFactory
		: public cppcomponents::define_interface <
		cppcomponents::uuid < 0xe59a4607, 0x6b30, 0x483d, 0x9743, 0x6a0d91102e51 >>
	{


		use<cppcomponents::InterfaceUnknown> Init(use<ILoop>,cr_string filename,
			use<FsEventCallback>, int flags);

		CPPCOMPONENTS_CONSTRUCT(IFsEventFactory, Init);
	}; 
	inline std::string FsEventId(){ return "cppcomponents_libuv_dll!FsEvent"; }
	typedef runtime_class<FsEventId, object_interfaces<IFsEvent>, factory_interface<IFsEventFactory>> FsEvent_t;
	typedef use_runtime_class<FsEvent_t> FsEvent;

	struct IMutex
		: cppcomponents::define_interface <
		cppcomponents::uuid < 0x5d6a475c, 0x82ab, 0x4ea1, 0xb564, 0xcf73b487e567 >>
	{
		void Lock();
		bool Trylock();
		void Unlock();
		void* UvHandle();

		// Calls destroy in destructor
		CPPCOMPONENTS_CONSTRUCT(IMutex, Lock, Trylock, Unlock,UvHandle);
	};

	struct IMutexFactory
		: cppcomponents::define_interface <
		cppcomponents::uuid < 0x778eef11, 0x1d5e, 0x40f5, 0xb9f5, 0xdb0808ceb18c >>
	{
		use<cppcomponents::InterfaceUnknown> Init();

		CPPCOMPONENTS_CONSTRUCT(IMutexFactory, Init);
	};

	inline std::string MutexId(){ return "cppcomponents_libuv_dll!Mutex"; }
	typedef runtime_class<MutexId, object_interfaces<IMutex>, factory_interface<IMutexFactory>> Mutex_t;
	typedef use_runtime_class<Mutex_t> Mutex;


	struct IRwlock
		: cppcomponents::define_interface <
		cppcomponents::uuid < 0x3e547e44, 0xda43, 0x4457, 0xaee2, 0xb985f1ee436e >>
	{
		void Rdlock();
		bool Tryrdlock();
		void Rdunlock();
		void Wrlock();
		bool Trywrlock();
		void Wrunlock();


		// Calls destroy in destructor
		CPPCOMPONENTS_CONSTRUCT(IRwlock,Rdlock,Tryrdlock,Rdunlock,Wrlock,Trywrlock,Wrunlock);
	};

	struct IRwlockFactory
		: cppcomponents::define_interface <
		cppcomponents::uuid < 0x7a8087ac, 0x4a33, 0x46b1, 0x8c28, 0xdc0066ed590c >>
	{
		use<cppcomponents::InterfaceUnknown> Init();

		CPPCOMPONENTS_CONSTRUCT(IRwlockFactory, Init);
	};
	inline std::string RwlockId(){ return "cppcomponents_libuv_dll!Rwlock"; }
	typedef runtime_class<RwlockId, object_interfaces<IRwlock>, factory_interface<IRwlockFactory>> Rwlock_t;
	typedef use_runtime_class<Rwlock_t> Rwlock;


	struct ISemaphore
		: cppcomponents::define_interface <
		cppcomponents::uuid < 0xa0c6b903, 0x62be, 0x462a, 0xbd16, 0x5be9dabe37b4 >>
	{
		void Post();
		void Wait();
		bool Trywait();

		// Calls destroy in destructor
		CPPCOMPONENTS_CONSTRUCT(ISemaphore, Post, Wait, Trywait);
	};

	struct ISemaphoreFactory
		: cppcomponents::define_interface <
		cppcomponents::uuid < 0x8cf50ef7, 0x747c, 0x4bcd, 0xbf5d, 0x59cdbf5e9074 >>
	{
		use<cppcomponents::InterfaceUnknown> Init(unsigned int value);

		CPPCOMPONENTS_CONSTRUCT(ISemaphoreFactory, Init);
	};
	inline std::string SemaphoreId(){ return "cppcomponents_libuv_dll!Semaphore"; }
	typedef runtime_class<SemaphoreId, object_interfaces<ISemaphore>, factory_interface<ISemaphoreFactory>> Semaphore_t;
	typedef use_runtime_class<Semaphore_t> Semaphore;

	struct IConditionVariable
		: cppcomponents::define_interface <
		cppcomponents::uuid < 0xe39e7414, 0x5caa, 0x4cb3, 0x8083, 0x925a432bb933 >>
	{
		void Signal();
		void Broadcast();
		void Wait(use<IMutex>);
		bool Timedwait(use<IMutex>, std::uint64_t timeout);

		// Calls destroy in destructor
		CPPCOMPONENTS_CONSTRUCT(IConditionVariable, Signal,Broadcast,
			Wait,Timedwait);
	};

	struct IConditionVariableFactory
		: cppcomponents::define_interface <
		cppcomponents::uuid < 0x4f1e7975, 0x8652, 0x42e4, 0x8fd7, 0xb79b4900864e >>
	{
		use<cppcomponents::InterfaceUnknown> Init();

		CPPCOMPONENTS_CONSTRUCT(IConditionVariableFactory, Init);
	};
	inline std::string ConditionVariableId(){ return "cppcomponents_libuv_dll!ConditionVariable"; }
	typedef runtime_class<ConditionVariableId, object_interfaces<IConditionVariable>, factory_interface<IConditionVariableFactory>> ConditionVariable_t;
	typedef use_runtime_class<ConditionVariable_t> ConditionVariable;


	struct IBarrier
		: public cppcomponents::define_interface <
		cppcomponents::uuid < 0x69a0cb70, 0x74d1, 0x47d5, 0x8454, 0xfa04640f1ec9 >>
	{
		void Wait();

		CPPCOMPONENTS_CONSTRUCT(IBarrier, Wait);
	};

	struct IBarrierFactory
		: public cppcomponents::define_interface <
		cppcomponents::uuid < 0xd6bbc581, 0xcbe2, 0x498f, 0x861b, 0x6d9e29aef114 >>
	{
		use<cppcomponents::InterfaceUnknown> Init(unsigned int count);
	};

	inline std::string BarrierId(){ return "cppcomponents_libuv_dll!Barrier"; }
	typedef runtime_class<BarrierId, object_interfaces<IBarrier>, factory_interface<IBarrierFactory>> Barrier_t;
	typedef use_runtime_class<Barrier_t> Barrier;



	// uv_once is not implemented use std::once;


	// Thead functions not implemented, use std::thread


	struct Executor : cppcomponents::LoopExecutor{
		Prepare prep_;

		explicit Executor(use<ILoop> loop) :prep_{ loop }{
			cppcomponents::use<cppcomponents::ILoopExecutor> exec = *this;
			prep_.Start([exec](cppcomponents::use<IPrepare>, int){
				exec.RunQueuedClosures();
			});
		}

		Executor(const Executor&) = delete;
		Executor& operator=(const Executor&) = delete;

		~Executor(){
			prep_.Stop();
		}

		void Stop(){
			prep_.Unref();
		}

	};

}

#endif