#include "Process.h"

Process::Process(int at, int pid, int ct, int toi, IORequests ior[])
{
	ArrivalTime = at;
	ProcessID = pid;
	CPUTime = ct;
	TimesOfIO = toi;
	IoRequests = ior;
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

IORequests* Process::getIORequests()
{
	return IoRequests;
}
