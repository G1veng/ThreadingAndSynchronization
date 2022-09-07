#include "synchronization.h"


#pragma region Mutex
std::mutex mutexTestVar;


void synchronization::MutexExample(void)
{
  mutexTestVar.lock();

  std::cout << "Mutex is used by thread: " << GetCurrentThreadId() << std::endl;
  std::cout << "No other thread can't get access now" << std::endl;
  //Sleep(3000);
  std::this_thread::sleep_for(std::chrono::seconds(3));

  mutexTestVar.unlock();
}


void synchronization::MutexTest(void) {
  std::thread t1(MutexExample);
  std::thread t2(MutexExample);

  t1.join();
  t2.join();
}
#pragma endregion


#pragma region Semaphore
std::binary_semaphore
  smphSignalMainToThread(0),
  smphSignalThreadToMain(0);

void synchronization::ThreadProc(void)
{
  smphSignalMainToThread.acquire();

  std::cout << "[thread] Got the signal\n";

  std::this_thread::sleep_for(std::chrono::seconds(3));

  std::cout << "[thread] Send the signal\n";

  smphSignalThreadToMain.release();
}


void synchronization::SemaphoreTest(void) {
  std::thread thrWorker(ThreadProc);

  std::cout << "[main] Send the signal\n";

  smphSignalMainToThread.release();

  smphSignalThreadToMain.acquire();

  std::cout << "[main] Got the signal\n";
  thrWorker.join();
}
#pragma endregion


#pragma region Event
HANDLE hEvent1;
int result = 0;
HANDLE hThr;
unsigned long uThrID;


void Thread(void* pParams)
{  
  result = 1 + 1;
  std::this_thread::sleep_for(std::chrono::seconds(3));

  SetEvent(hEvent1); 
}


void TestEvent() {
  hEvent1 = CreateEvent(NULL, FALSE, FALSE, NULL);
  auto hThr = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)Thread, NULL, 0, &uThrID);

  WaitForSingleObject(hEvent1, INFINITE);

  std::cout << "Work done result is " << result << std::endl;
}
#pragma endregion


#pragma region waitabletimers

VOID CALLBACK TimerAPCProc(
  LPVOID lpArg,               // Data value
  DWORD dwTimerLowValue,      // Timer low value
  DWORD dwTimerHighValue)    // Timer high value

{
  synchronization::MYDATA *pMyData = (synchronization::MYDATA*)lpArg;

  std::cout << "Result: " << pMyData->dwValue << std::endl;
//  MessageBeep(0);
}

void TestWaitableTimer(void) {

  HANDLE          hTimer;
  BOOL            bSuccess;
  __int64         qwDueTime;
  LARGE_INTEGER   liDueTime;
  synchronization::MYDATA          MyData;

  MyData.szText = ("This is my data");
  MyData.dwValue = 100;

  hTimer = CreateWaitableTimer(
    NULL,                   
    FALSE,                  
    TEXT("MyTimer"));
  
  qwDueTime = -3 * _SECOND;

  
  liDueTime.LowPart = (DWORD)(qwDueTime & 0xFFFFFFFF);
  liDueTime.HighPart = (LONG)(qwDueTime >> 32);

  bSuccess = SetWaitableTimer(
    hTimer,
    &liDueTime,
    1,
    TimerAPCProc,
    &MyData,
    FALSE);

  if (bSuccess)
  {
    for (; MyData.dwValue < 1000; MyData.dwValue += 100)
    {
      SleepEx(
        INFINITE,
        TRUE);
    }

  }
  else
  {
    printf("SetWaitableTimer failed with error %d\n", GetLastError());
  }

    
  CloseHandle(hTimer);
}

#pragma endregion


#pragma region criticalsection
CRITICAL_SECTION cs;
int resultCS = 0;
HANDLE hThrCS;
unsigned long uThrIDCS;

void ThreadCS(void* pParams)
{ 
  EnterCriticalSection(&cs);
  std::cout << "Entered critical section in thread...counting..." << std::endl;

  std::this_thread::sleep_for(std::chrono::seconds(3));

  resultCS = 1 + 1;
  LeaveCriticalSection(&cs);
  
}


void TestCriticalSection(void) {
  InitializeCriticalSection(&cs);
  hThrCS = CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)ThreadCS, NULL, 0, &uThrIDCS);

  std::this_thread::sleep_for(std::chrono::seconds(1));

  while (1) {
    if (!TryEnterCriticalSection(&cs)) {
      std::cout << "Do other work" << std::endl;
      std::this_thread::sleep_for(std::chrono::seconds(1));
    }

    else {
      EnterCriticalSection(&cs);

      std::cout << "Entered critical section in main...printing..." << std::endl;
      std::cout << "Result is " << resultCS << std::endl;

      LeaveCriticalSection(&cs);
      break;
    }
  } 
}

#pragma endregion


void synchronization::TestSynchronization(void) {
  ShowChoices();
  int userChoice = GetInt(1, METHODS_COUNT + 1);

  StartMethod(userChoice);
}


void synchronization::StartMethod(int methodNum) {
  if (methodNum == MUTEX) {
    MutexTest();
  }

  if (methodNum == SEMAPHORE) {
    SemaphoreTest();
  }

  if (methodNum == EVENT) {
    TestEvent();
  }

  if (methodNum == WAITABLE_TIMER) {
    TestWaitableTimer();
  }

  if (methodNum == CRITICAL_SECTION_ENUM) {
    TestCriticalSection();
  }
}


void synchronization::ShowChoices(void){
  std::cout << "Choose sync method: " << std::endl;
  std::cout << "1 - Mutex" << std::endl;
  std::cout << "2 - Semaphore" << std::endl;
  std::cout << "3 - Event" << std::endl;
  std::cout << "4 - WaitableTimer" << std::endl;
  std::cout << "5 - CriticalSection" << std::endl;
}

