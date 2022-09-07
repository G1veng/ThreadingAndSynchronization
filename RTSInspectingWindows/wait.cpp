#include "wait.h"


unsigned int __stdcall DoSomeWork(void* data) {
  std::cout << "Doing some work..." << std::endl;
  Sleep(1000);
  std::cout << "Main thread is still waiting..." << std::endl;
  Sleep(4000);
  std::cout << "Done with work" << std::endl;
  return 0;
}


void TestWait(void) {
	HANDLE myThread = (HANDLE)_beginthreadex(0, 0, &DoSomeWork, 0, 0, 0);

	WaitForSingleObject(myThread, INFINITE);

	CloseHandle(myThread);
}

