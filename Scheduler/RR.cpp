#pragma once
#include "RR.h"

void RR::ScheduleAlgo() {}
//{
//	if (State == "BUSY" && RunningProcess->getCPUTime()-RunningProcess->getTimeCounter()!=RunningProcess->getTimesOfIO())  // assuming TimesOfIO is RequestTime
//	{
//		RunningTimeSlice--; //work on running process until time slice ends;
//		RunningProcess->decrmntTimeCounter();
//	}
//	if (State=="BUSY" && RunningProcess->getCPUTime() - RunningProcess->getTimeCounter() == RunningProcess->getTimesOfIO())
//	{
//		pScheduler->AddtoBLK(RunningProcess);
//		State = "IDLE";
//	}
//	if (State=="BUSY" && RunningProcess->getTimeCounter() == 0)  //Terminates process if its finishes processing
//	{
//		RunningProcess->setTerminationT(pScheduler->getTime());
//		RunningProcess->setTRT(pScheduler->getTime() - RunningProcess->getArrivalTime());
//		State = "IDLE";
//		pScheduler->AddtoTRM(RunningProcess);
//	}
//
//	if (RunningTimeSlice == 0 && State=="BUSY") //requeue process after timeslice ends
//	{
//		AddToRDY(RunningProcess);
//		 
//		State = "IDLE";
//		
//	}
//
//	if (State == "IDLE" && !RDY.isEmpty()) 
//	{
//		RunningTimeSlice = pScheduler->getTimeSlice();
//		RDY.deQueue(RunningProcess);
//		RunningProcess->setState("RUN");
//		RunningProcess->setRT(pScheduler->getTime() - RunningProcess->getArrivalTime()); //need to set arrival time in execute
//		State = "BUSY";
//	}
//	if (State == "IDLE") {
//		IdleTime++;
//	}
//}
void RR::Simulate() {
	if (State == "IDLE" && !RDY.isEmpty()) {
		RDY.deQueue(RunningProcess);
		State = "BUSY";
	}
	
	if (RunningProcess) {
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
}

void RR::AddToRDY(Process* Prc)
{
	RDY.enQueue(Prc);
	Prc->setState("RDY"); //to set the state to know which list to move the process to in the scheduler
}
void RR::TerminateRandomProcess()
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
