#include "createProcess.h"


void createprocess::TestCreateProcess(void) {
  STARTUPINFO si;
  PROCESS_INFORMATION pi;
  ZeroMemory(&si, sizeof(si));
  ZeroMemory(&pi, sizeof(pi));
  BOOL bCreateProcess = NULL;
  bCreateProcess = CreateProcess(
    L"C:\\Users\\danii\\AppData\\Local\\Postman\\Postman.exe",
    NULL,
    NULL,
    NULL,
    false,
    createprocess::ChoosePriority(),
    NULL,
    NULL,
    &si,
    &pi
  );


  if (bCreateProcess == false) {
    std::cout << "Fail in process creation, Error No - " << GetLastError() << std::endl;
  }

  else {
    std::cout << "Create process success" << std::endl;

    WaitForSingleObject(pi.hProcess, INFINITE);

    CloseHandle(pi.hThread);
    CloseHandle(pi.hProcess);
  }
}


int createprocess::ChoosePriority(void) {
  int priority = NORMAL_PRIORITY_CLASS;

  std::cout << "Choose priority" << std::endl;
  std::cout << "1 - ABOVE_NORMAL_PRIORITY_CLASS" << std::endl;
  std::cout << "2 - BELOW_NORMAL_PRIORITY_CLASS" << std::endl;
  std::cout << "3 - HIGH_PRIORITY_CLASS" << std::endl;
  std::cout << "4 - IDLE_PRIORITY_CLASS" << std::endl;
  std::cout << "5 - NORMAL_PRIORITY_CLASS" << std::endl;
  std::cout << "6 - REALTIME_PRIORITY_CLASS" << std::endl;
  std::cout << "Enter number: ";

  priority = GetInt(1, PRIORITY_COUNT + 1);

  return GetPriorityType(priority);
}


int createprocess::GetPriorityType(int priority) {
  if (priority == 1) {
    return ABOVE_NORMAL_PRIORITY_CLASS;
  }
  else if (priority == 2) {
    return BELOW_NORMAL_PRIORITY_CLASS;
  }
  else if (priority == 3) {
    return HIGH_PRIORITY_CLASS;
  }
  else if (priority == 4) {
    return IDLE_PRIORITY_CLASS;
  }
  else if (priority == 5) {
    return NORMAL_PRIORITY_CLASS;
  }
  else if (priority == 6) {
    return REALTIME_PRIORITY_CLASS;
  }

  throw new std::exception("Nonexisting priority");
}