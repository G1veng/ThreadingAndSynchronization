#pragma once

#include "input.h"
#include <iostream>
#include <Windows.h>

namespace createprocess {
	#define PRIORITY_COUNT 6

	void TestCreateProcess(void);

	int ChoosePriority(void);

	int GetPriorityType(int priority);
}