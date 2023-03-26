#include "Process.h"

Process::Process(int pid, int at, int ct, int toi, IORequests ior[])
{
  
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

IORequests** Process::getIORequests()
{
	return IoRequests;
}
