#include "Process.h"

Process::Process(int at, int pid, int ct,int deadline, int toi, IORequests ior[])
{
	ArrivalTime = at;
	ProcessID = pid;
	CPUTime = ct;
	Deadline = deadline;
	TimesOfIO = toi;
	TimeCounter = ct;
	isChild = 0;
	isParent = 0;
	Child = nullptr;
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

int Process::getIO_D()
{
	IORequests* temp;
	int sum = 0;
	while (UsedIoRequests.deQueue(temp))
	{
		sum += temp->Duration;
	}
		
	return sum;
}

int Process::getTimesOfIO()
{
	return TimesOfIO;
}

Queue<IORequests*> Process::getIORequests()
{
	return IoRequests;
}

int Process::getDeadline()
{
	return Deadline;
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
	if(ProcessID == 11){
		int x = 0;
	}
	TurnAroundDuration = TerminationTime - ArrivalTime;
}

void Process::setWT()
{
	if (ProcessID == 5) {
		int x=0;
	}
	WaitingTime = TurnAroundDuration - CPUTime;
}

int Process::getWT()
{
	return WaitingTime;
}

void Process::setRT(int Time)
{
	ResponseTime = Time - ArrivalTime;
}

int Process::getRT()
{
	return ResponseTime;
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
	UsedIoRequests.enQueue(iorptr);
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

void Process::setchild(Process*P) {
	Child = P;
	P->isChild = 1;
	isParent = 1;
}
bool Process::ischild()
{
	return isChild;
}
bool Process::isparent() {

	if (Child)
	{
		return 1;
	}
	else
	{
		return 0;
	}
}

int Process::getChildID()
{
	return Child->ProcessID;
}

ostream& operator<<(ostream& os, const Process& process)
{
	os << process.ProcessID;
	return os;
}
