#pragma once
#include "RR.h"

void RR::ScheduleAlgo()
{
	if (State == "BUSY" && RunningProcess->getCPUTime()-RunningProcess->getTimeCounter()!=RunningProcess->getTimesOfIO())  // assuming TimesOfIO is RequestTime
	{
		RunningTimeSlice--; //work on running process until time slice ends;
		RunningProcess->decrmntTimeCounter();
	}
	if (State=="BUSY" && RunningProcess->getCPUTime() - RunningProcess->getTimeCounter() == RunningProcess->getTimesOfIO())
	{
		pScheduler->AddtoBLK(RunningProcess);
		State = "IDLE";
	}
	if (State=="BUSY" && RunningProcess->getTimeCounter() == 0)  //Terminates process if its finishes processing
	{
		RunningProcess->setTerminationT(pScheduler->getTime());
		RunningProcess->setTRT(pScheduler->getTime() - RunningProcess->getArrivalTime());
		State = "IDLE";
		pScheduler->AddtoTRM(RunningProcess);
	}

	if (RunningTimeSlice == 0 && State=="BUSY") //requeue process after timeslice ends
	{
		AddToRDY(RunningProcess);
		 
		State = "IDLE";
		
	}

	if (State == "IDLE" && !RDY.isEmpty()) 
	{
		RunningTimeSlice = pScheduler->getTimeSlice();
		RDY.deQueue(RunningProcess);
		RunningProcess->setState("RUN");
		RunningProcess->setRT(pScheduler->getTime() - RunningProcess->getArrivalTime()); //need to set arrival time in execute
		State = "BUSY";
	}
	if (State == "IDLE") {
		IdleTime++;
	}





}

void RR::AddToRDY(Process* Prc)
{
	RDY.enQueue(Prc);
	Prc->setState("RDY"); //to set the state to know which list to move the process to in the scheduler
}
RR::RR(Scheduler* scheduler)
{
	pScheduler = scheduler;
}
