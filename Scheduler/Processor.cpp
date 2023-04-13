#include "Processor.h"
#include <random>

void Processor::setState(string state)
{
	State = state;
}

int Processor::generateRandomNumber()
{
	

	return rand() % 100 + 1; // generate a random number between 1 and 100
}


bool Processor::isRunning()
{
	if(RunningProcess != nullptr)
	{
		return true;
	}
	return false;
}

Process* Processor::getRunning()
{
	return RunningProcess;
}

Processor::Processor()
{
	srand(time(NULL)); // seed the random number generator with the current time
	State = "IDLE";
	IdleTime = 0; //initializing idletime to zero
	ExpectedFinishTime = 0;
	RunningProcess = nullptr; //?? add or is state sufficient "TO BE EDITED"
}

ostream& operator<<(ostream& os, const Processor& processor)
{
	os << "[ " << processor.Type << " ]";
	return os;
}
