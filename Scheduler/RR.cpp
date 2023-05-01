#pragma once
#include "RR.h"

void RR::ScheduleAlgo()
{
	IORequests* CurrentIO=nullptr; // TO BE ABLE TO PEAK/DEQUEUE FROM THE IO QUEUE
	if (RunningProcess!=nullptr && RunningProcess->getCPUTime() - RunningProcess->getTimeCounter() != CurrentIO->RequestTime)  // assuming TimesOfIO is RequestTime
	{
		RunningTimeSlice--; //work on running process until time slice ends;
		RunningProcess->decrmntTimeCounter();
	}
	if (RunningProcess!=nullptr && RunningProcess->getCPUTime() - RunningProcess->getTimeCounter() == CurrentIO->RequestTime)
	{
		pScheduler->AddtoBLK(RunningProcess);
		RunningProcess = nullptr;
	}
	if (RunningProcess && RunningProcess->getTimeCounter() == 0)  //Terminates process if its finishes processing
	{
		RunningProcess->setTerminationT(pScheduler->getTime());
		RunningProcess->setTRT();
		pScheduler->AddtoTRM(RunningProcess);
		RunningProcess = nullptr;
		
	}

	if (RunningTimeSlice == 0 && RunningProcess) //requeue process after timeslice ends
	{
		AddToRDY(RunningProcess);
		 
		RunningProcess = nullptr;
		
	}

	if (!RunningProcess && !RDY.isEmpty())
	{
		RunningTimeSlice = TimeSlice;
		RDY.deQueue(RunningProcess);
		RunningProcess->setState("RUN");
		RunningProcess->setRT(pScheduler->getTime()); //need to set arrival time in execute
		RunningProcess->getIORequests().peek(CurrentIO);
	}
	if (!RunningProcess) {
		IdleTime++;
	}
	else {
		BusyTime++;
	}
}
void RR::Simulate(){}


void RR::AddToRDY(Process* Prc)
{
	RDY.enQueue(Prc);
	Prc->setState("RDY"); //to set the state to know which list to move the process to in the scheduler
}
void RR::TerminateRandomProcess(int randomnumber)
{
}

void RR::setRTF(int RTF_)
{
	RTF = RTF_;
}

void RR::setTimeSlice(int TimeSlice_)
{
	TimeSlice = TimeSlice_;
}

RR::RR(Scheduler* scheduler)
{
	pScheduler = scheduler;
	Type = "RR";
}

void RR::PrintRDY()
{
	RDY.Print();
}

int RR::getRDYCount()
{
	return RDY.getCount();
}

int RR::MigrationNumber; // changes only from new->rdy
int RR::NumberOfProcesses;
int RR::RTF; //makes more sense to make this a static data member too
int RR::TimeSlice;
