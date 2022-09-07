#include "beginthreadex.h"


void beginthreadindex::TestBeginThreadIndex(void) {
  std::cout << "Enter amount of threads:";
  int threadCount = GetInt(1, INT_MAX);

  HANDLE* myThreads = new HANDLE[threadCount];

  for (int i = 0; i < threadCount; i++) {
    myThreads[i] = (HANDLE)_beginthreadex(0, 0, &mythread, 0, CREATE_SUSPENDED, 0);
  }

  if (myThreads == NULL) {
    throw new std::exception("Could't create thread");
  }

  for (int i = 0; i < threadCount; i++) {
    if (myThreads[i] != 0) {
      SetThreadPriority(myThreads[i], ChoosePriority());
    }
  }

  for (int i = 0; i < threadCount; i++) {
    std::cout << "Thread " << i << "; Priority is " << GetThreadPriority(myThreads[i]) << std::endl;
  }

  for (int i = 0; i < threadCount; i++) {
    ResumeThread(myThreads[i]);
  }

  WaitForMultipleObjects(threadCount, myThreads, true, INFINITE);

  for (int i = 0; i < threadCount; i++) {
    CloseHandle(myThreads[i]);
  }
}


unsigned int __stdcall beginthreadindex::mythread(void* data)
{
  std::cout << GetCurrentThreadId() << std::endl;

  return 0;
}


int beginthreadindex::ChoosePriority(void) {
  int priority = THREAD_PRIORITY_NORMAL;

  std::cout << "Choose priority" << std::endl;
  std::cout << "1 - THREAD_MODE_BACKGROUND_BEGIN - '0'" << std::endl;
  std::cout << "2 - THREAD_MODE_BACKGROUND_END - '0'" << std::endl;
  std::cout << "3 - THREAD_PRIORITY_ABOVE_NORMAL - '1'" << std::endl;
  std::cout << "4 - THREAD_PRIORITY_BELOW_NORMAL - '-1'" << std::endl;
  std::cout << "5 - THREAD_PRIORITY_HIGHEST - '2'" << std::endl;
  std::cout << "6 - THREAD_PRIORITY_IDLE - '-15'" << std::endl;
  std::cout << "7 - THREAD_PRIORITY_LOWEST - '-2'" << std::endl;
  std::cout << "8 - THREAD_PRIORITY_NORMAL - '0'" << std::endl;
  std::cout << "9 - THREAD_PRIORITY_TIME_CRITICAL - '15'" << std::endl;
  std::cout << "Enter number: ";

  priority = GetInt(1, PRIORITY_COUNT + 1);

  return GetPriorityType(priority);
}


int beginthreadindex::GetPriorityType(int priorityNum) {
  if (priorityNum == 1) {
    return THREAD_MODE_BACKGROUND_BEGIN;
  }
  if (priorityNum == 2) {
    return THREAD_MODE_BACKGROUND_END;
  }
  if (priorityNum == 3) {
    return THREAD_PRIORITY_ABOVE_NORMAL;
  }
  if (priorityNum == 4) {
    return THREAD_PRIORITY_BELOW_NORMAL;
  }
  if (priorityNum == 5) {
    return THREAD_PRIORITY_HIGHEST;
  }
  if (priorityNum == 6) {
    return THREAD_PRIORITY_IDLE;
  }
  if (priorityNum == 7) {
    return THREAD_PRIORITY_LOWEST;
  }
  if (priorityNum == 8) {
    return THREAD_PRIORITY_NORMAL;
  }
  if (priorityNum == 9) {
    return THREAD_PRIORITY_TIME_CRITICAL;
  }
  throw new std::exception("Nonexisting priority");
}