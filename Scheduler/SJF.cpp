#include "SJF.h"

void SJF::ScheduleAlgo()
{
	Process* Prc;
	RDY.deQueue(Prc);
	IORequests *i = Prc->getIORequests();
	int Time;
	Time = pScheduler->getTime();
	int t=0;
	while (Time < 1000)//Temporary condition to test, this is the while for every timestep , the end condition would be in this while.
	{
		if (Time == i[in].getRequestTime())
		{
			pScheduler->AddtoBLK(Prc);
			t = Time+ i->getDuration();
		}
		if (Time == t) {
			RDY.enQueue(Prc, Prc->getCPUTime() - i->getRequestTime());
			in++;
		}
		Time++;//Increments the time 	
		if (in == Prc->getTimesOfIO())
			in = 0;
	}
}

void SJF::AddToRDY(Process* Prc)
{
	RDY.enQueue(Prc, Prc->getCPUTime());
}

SJF::SJF(Scheduler* scheduler)
{
	pScheduler = scheduler;
}

