g++ -I./../../../cppcomponents -I./../../../libuv/include/ ../unit_test_exe.cpp  -std=c++11 -D_WIN32_WINNT=0x060 -DWIN32_LEAN_AND_MEAN -DSRWLOCK=PVOID 