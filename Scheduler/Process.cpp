#include "Process.h"

Process::Process(int at, int pid, int ct, int toi, IORequests ior[])
{
	ArrivalTime = at;
	ProcessID = pid;
	CPUTime = ct;
	TimesOfIO = toi;
	TimeCounter = ct;
	isChild = 0;
	IORequests* io;//temp variable to enqueue
	for (int i = 0; i < toi; i++)
	{
		io = &ior[i];
		IoRequests.enQueue(io);
	}

	
}

int Process::getTerminationTime()
{
	return TerminationTime;
}

int Process::getTimeCounter()
{
	return TimeCounter;
}

int Process::getProcessID()
{
	return ProcessID;
}

int Process::getArrivalTime()
{
	return ArrivalTime;
}

int Process::getCPUTime()
{
	return CPUTime;
}

int Process::getTimesOfIO()
{
	return TimesOfIO;
}

Queue<IORequests*> Process::getIORequests()
{
	return IoRequests;
}


void Process::setArrivalTime(int Time)
{
	ArrivalTime = Time;
}

void Process::setState(string S)
{
	State = S;
}

void Process::setCPUTime(int Time)
{
	CPUTime = Time;
}

void Process::setTerminationT(int Time)
{
	TerminationTime = Time;
}

void Process::setTRT()
{
	TerminationTime = TerminationTime - ArrivalTime;
}

void Process::setWT(int Time)
{
	WaitingTime = TurnAroundDuration - CPUTime;
}

void Process::setRT(int Time)
{
	ResponseTime = ArrivalTime - Time;
}

void Process::decrmntTimeCounter()
{
	TimeCounter--;
}

IORequests* Process::getIORequest()
{
	IORequests* iorptr;
	IoRequests.peek(iorptr);
	return iorptr;
}

void Process::RemoveIORequest()
{
	IORequests* iorptr;
	IoRequests.deQueue(iorptr);
	TimesOfIO--;
}

bool Process::checkIORequestDurationTime()
{
	IORequests* iorptr;
	IoRequests.peek(iorptr);
	iorptr->Duration--;
	if (iorptr->Duration==0)
	{
		RemoveIORequest();
		return true;
	}
	return false;
}

bool Process::ischild()
{
	return isChild;
}

ostream& operator<<(ostream& os, const Process& process)
{
	os << process.ProcessID;
	return os;
}
