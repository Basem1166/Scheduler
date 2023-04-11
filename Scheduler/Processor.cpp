#include "Processor.h"
#include <cstdlib>
#include <ctime>

void Processor::setState(string state)
{
	State = state;
}

int Processor::generateRandomNumber()
{
	srand(time(NULL)); // seed the random number generator with the current time

	return rand() % 100 + 1; // generate a random number between 1 and 100
}


Processor::Processor()
{
	State = "IDLE";
	IdleTime = 0; //initializing idletime to zero
	ExpectedFinishTime = 0;
	RunningProcess = nullptr; //?? add or is state sufficient "TO BE EDITED"
}


