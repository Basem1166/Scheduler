#include "Processor.h"

void Processor::setState(string state)
{
	State = state;
}

Processor::Processor()
{
	State = "IDLE";
	ExpectedFinishTime = 0;
}


