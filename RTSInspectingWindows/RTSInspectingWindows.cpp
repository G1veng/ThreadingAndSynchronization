#include "createProcess.h"
#include "input.h"
#include "beginthreadex.h"
#include "wait.h"
#include "synchronization.h"


#define PROGRAM_COUNT 4
#define CREATE_PROCESS 1
#define BEGIN_THREAD_INDEX 2
#define WAIT 3
#define SYNCHRONIZATION 4


void Startup(void);
void Greetings(void);
void ShowChoices(void);
void StartPrograms(int programNum);


int main()
{
  Startup();

  return 0;
}


void Startup(void) {
  Greetings();

  do {
    ShowChoices();

    int userChoice = GetInt(1, PROGRAM_COUNT + 2);

    if (userChoice == 5) {
      break;
    }

    StartPrograms(userChoice);
  } while (true);
}


void Greetings(void) {
  std::cout << "Programm created by student of 404 group: Azarov Daniil, Ruchlova Ksenia, Shishko Daniil" << std::endl;
}


void ShowChoices(void){
  std::cout << "Choose program: " << std::endl;
  std::cout << "1 - creation of process 'CreateProcess' with priority set" << std::endl;
  std::cout << "2 - creation of threads '_beginthreadex' with relative priority set" << std::endl;
  std::cout << "3 - using 'wait' functions for wait threads to end" << std::endl;
  std::cout << "4 - using mechanichs of synchronization" << std::endl;
  std::cout << "5 - Exit" << std::endl;
}


void StartPrograms(int programNum) {
  if (programNum == CREATE_PROCESS) {
    createprocess::TestCreateProcess();
  }

  if (programNum == BEGIN_THREAD_INDEX) {
    beginthreadindex::TestBeginThreadIndex();
  }
  
  if (programNum == WAIT) {
    TestWait();
  }

  if (programNum == SYNCHRONIZATION) {
    synchronization::TestSynchronization();
  }
}