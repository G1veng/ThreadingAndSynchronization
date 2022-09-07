#pragma once

#include <process.h>
#include <Windows.h>
#include "input.h"

namespace beginthreadindex {
	#define PRIORITY_COUNT 9

	void TestBeginThreadIndex(void);

	unsigned int __stdcall mythread(void* data);

	int GetPriorityType(int priorityNum);

	int ChoosePriority(void);
}