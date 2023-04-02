#include "RR.h"

void RR::ScheduleAlgo()
{
}

void RR::AddToRDY(Process* Prc)
{
	RDY.enQueue(Prc);
}
RR::RR(Scheduler scheduler)
{
	pScheduler = &scheduler;
}
