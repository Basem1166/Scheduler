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

void SJF::Simulate()
{
	if (State == "IDLE" && !RDY.isEmpty()) {

		RDY.deQueue(RunningProcess);
		State = "BUSY";
	}

	if (!RunningProcess)
		return;
	int x = generateRandomNumber();
	if (x >= 1 && x <= 15) {
		pScheduler->AddtoBLK(RunningProcess);
		State = "IDLE";
	}
	else if (x >= 20 && x <= 30) {
		AddToRDY(RunningProcess);
		State = "IDLE";
	}
	else if (x >= 50 && x <= 60) {
		pScheduler->AddtoTRM(RunningProcess);
		State = "IDLE";
	}
}

void SJF::TerminateRandomProcess()
{
}

SJF::SJF(Scheduler* scheduler)
{
	pScheduler = scheduler;
}

