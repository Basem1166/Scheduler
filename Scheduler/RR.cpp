#pragma once
#include "RR.h"

void RR::ScheduleAlgo(int Time)
{

	OverHeat();
	if (State == "STOP")
	{
		return;
	}
	

	IORequests* CurrentIO = nullptr; // TO BE ABLE TO PEAK/DEQUEUE FROM THE IO QUEUE
	if (RunningProcess) {
		RunningProcess->getIORequests().peek(CurrentIO);
	}
	
	if (RunningProcess!=nullptr && CurrentIO && RunningProcess->getCPUTime() - RunningProcess->getTimeCounter() == CurrentIO->RequestTime) //checks if it ran for the IO_R to add it to BLK list
	{
		pScheduler->AddtoBLK(RunningProcess);
		ExpectedFinishTime -= RunningProcess->getTimeCounter();
		RunningProcess = nullptr;
	}
	
	if (RunningProcess && RunningProcess->getTimeCounter() == 0)  //Terminates process if its finishes processing
	{



		pScheduler->AddtoTRM(RunningProcess);
		RunningProcess = nullptr;
		
	}
	if (RunningProcess != nullptr && RunningProcess->getTimeCounter() != 0)   //Decrements the remaining time & timeslice for process if it didnt finish its cpu time
	{
		RunningTimeSlice--; //work on running process until time slice ends;
		RunningProcess->decrmntTimeCounter();
		ExpectedFinishTime--;
	}

	if (RunningTimeSlice == 0 && RunningProcess) //requeue process after timeslice ends
	{
		ExpectedFinishTime -= RunningProcess->getTimeCounter();
		AddToRDY(RunningProcess);
		RunningProcess = nullptr;
		
	}

	while (!RunningProcess && !RDY.isEmpty()) //Adds new Process to RUN
	{
		RunningTimeSlice = TimeSlice;
		RDY.deQueue(RunningProcess);

		if (RunningProcess->getTimeCounter() < RTF) // check if it should migrate or not
		{
			if (pScheduler->Migrate(RunningProcess, 1)) {// call migrate function of the scheduler
				MigrationNumber++;
				ExpectedFinishTime -= RunningProcess->getTimeCounter();
				RunningProcess = nullptr;
				continue;
			}
		}

		RunningProcess->setState("RUN");
		if (RunningProcess->getRTCheck()) // to set RT first time it enters the RUN
		{
			RunningProcess->setRT(Time); //sets the Response time
			RunningProcess->setRTCheck(false);
		}
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
	addfinishtime(Prc);
}
void RR::TerminateProcess(int randomnumber,int mode)
{
}

Process* RR::StealProcess()
{
	Process* prc =nullptr;
	RDY.deQueue(prc);
	if (prc)
	{
		ExpectedFinishTime -= prc->getTimeCounter();
		
	}
	return prc;
}

void RR::setRTF(int RTF_)
{
	RTF = RTF_;
}
void RR::EmptyProcessor() {
	if (RunningProcess) {
		pScheduler->AddtoRDY(RunningProcess);
		RunningProcess = nullptr;
	}
	Process* prc;
	while (!RDY.isEmpty())
	{
		RDY.deQueue(prc);
		pScheduler->AddtoRDY(prc);
	}

}
//generic setter, getter and print functions 
string RR::getState() {

	return State;

}


void RR::setTimeSlice(int TimeSlice_)
{
	TimeSlice = TimeSlice_;
}

void RR::IncrementMigrationNumber()
{
	MigrationNumber++;
}

int RR::getMigrationNumber()
{
	return MigrationNumber;
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

string RR::getType()
{
	return Type;
}

int RR::getRDYCount()
{
	return RDY.getCount();
}

void RR::addfinishtime(Process* Prc) {
	ExpectedFinishTime += Prc->getTimeCounter();
}

int RR::getfinishtime() {
	return ExpectedFinishTime;
}

int RR::MigrationNumber = 0; // changes only from new->rdy
int RR::NumberOfProcesses;
int RR::RTF; //makes more sense to make this a static data member too
int RR::TimeSlice;
