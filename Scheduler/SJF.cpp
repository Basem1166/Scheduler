#include "SJF.h"

void SJF::ScheduleAlgo(int Time)

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
	
	if (RunningProcess != nullptr && CurrentIO && RunningProcess->getCPUTime() - RunningProcess->getTimeCounter() == CurrentIO->RequestTime)//checks if it ran for the IO_R to add it to BLK list
	{
		pScheduler->AddtoBLK(RunningProcess);
		ExpectedFinishTime -= RunningProcess->getTimeCounter();
		RunningProcess = nullptr;
	}
	if (RunningProcess != nullptr && RunningProcess->getTimeCounter()!=0  )   //Decrements the remaining time for process if it didnt finish its cpu time
	{
		RunningProcess->decrmntTimeCounter();
		ExpectedFinishTime--;

	}
	if (RunningProcess && RunningProcess->getTimeCounter() == 0)  //Terminates process if its finishes processing
	{

		pScheduler->AddtoTRM(RunningProcess);
		RunningProcess = nullptr;

	}
	
	if (!RunningProcess && !RDY.isEmpty()) //Adds new Process to RUN
	{
		RDY.deQueue(RunningProcess);
		RunningProcess->setState("RUN");
		RunningProcess->setRT(Time); //need to set arrival time in execute
		RunningProcess->getIORequests().peek(CurrentIO);
	}
	if (!RunningProcess) {
		IdleTime++; //Adds Idle time if there is no running process in the end of the algo
	}
	else {
		BusyTime++; //Adds Busy time if a process is currently running in the end of the algo
	}
}

void SJF::AddToRDY(Process* Prc)
{
	RDY.enQueue(Prc, Prc->getTimeCounter());
	addfinishtime(Prc);
}

void SJF::Simulate()
{}

void SJF::TerminateProcess(int randomnumber,int mode)
{
}
void SJF::EmptyProcessor() {
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
//Generic setter,getter and print functions
string SJF::getState() {

	return State;

}


Process* SJF::StealProcess()
{
	Process* prc = nullptr;
	RDY.deQueue(prc);
	if(prc)
	ExpectedFinishTime -= prc->getTimeCounter();
	return prc;
}

SJF::SJF(Scheduler* scheduler)
{
	pScheduler = scheduler;
	Type = "SJF";
}

void SJF::PrintRDY()
{
	RDY.Print();
}

int SJF::getRDYCount()
{
	return RDY.getCount();
}

string SJF::getType()
{
	return Type;
}

void SJF::addfinishtime(Process* Prc) {
	ExpectedFinishTime += (Prc->getTimeCounter());
}

int SJF::getfinishtime() {
	return ExpectedFinishTime;
}
