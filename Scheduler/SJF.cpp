#include "SJF.h"

void SJF::ScheduleAlgo()
{
	Process* Prc;
	RDY.deQueue(Prc);
	IORequests *i=Prc->getIORequests();
	int Time=gettime();
	int t;
	while (Time < 1000)//Temporary condition to test, this is the while for every timestep , the end condition would be in this while.
	{
		if (Time = i->getRequestTime())
		{
			AddtoBLK(Prc);
			t = Time+ i->getDuration();
		}
		if (Time = t)
			RDY.enQueue(Prc, Prc->getCPUTime()- i->getRequestTime());
		Time++;//Increments the time 		
	}
}

void SJF::AddToRDY(Process* Prc)
{
	RDY.enQueue(Prc, Prc->getCPUTime());
}
