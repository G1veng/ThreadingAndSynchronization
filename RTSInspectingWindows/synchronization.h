#pragma once


#include "input.h"
#include <thread>
#include <mutex>
#include <process.h>
#include <Windows.h>
#include <semaphore>
#include <chrono>
#include <list>
#include <tchar.h>

 
namespace synchronization {

	typedef struct _MYDATA {
		std::string szText;
		DWORD dwValue;
	} MYDATA;

	#define METHODS_COUNT 5
	#define MUTEX 1
	#define SEMAPHORE 2
	#define EVENT 3
	#define WAITABLE_TIMER 4
	#define CRITICAL_SECTION_ENUM 5
	#define _SECOND 10000000


	void TestSynchronization(void);

	void MutexExample(void);

	void StartMethod(int methodNum);

	void ShowChoices(void);

	void MutexTest(void);

	void ThreadProc(void);

	void SemaphoreTest(void);
}