#include "Processor.h"

void Processor::setState(string state)
{
	State = state;
}

Processor::Processor()
{
	State = "IDLE";
	IdleTime = 0; //initializing idletime to zero
	ExpectedFinishTime = 0;
	RunningProcess = nullptr; //?? add or is state sufficient "TO BE EDITED"
}


