#pragma once
#include "RR.h"

void RR::ScheduleAlgo()
{
	if (State == "IDLE") {
		RDY.deQueue(RunningProcess);
		RunningProcess->setRT(pScheduler->getTime());
		State = "BUSY";
	}
	if (RunningProcess->getTimeCounter() == 0) {
		pScheduler->AddtoTRM(RunningProcess);
		State = "IDLE";
	}



}

void RR::AddToRDY(Process* Prc)
{
	RDY.enQueue(Prc);
}
RR::RR(Scheduler* scheduler)
{
	pScheduler = scheduler;
}
