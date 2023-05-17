#include "EDF.h"

void EDF::ScheduleAlgo(int Time)
{
	OverHeat();
	if (State == "STOP")
	{
		return;
	}
	
	IORequests* CurrentIO = nullptr; // TO BE ABLE TO PEAK/DEQUEUE FROM THE IO QUEUE
	if (RunningProcess) {
		RunningProcess->getIORequests().peek(CurrentIO); //get the first IO in the queue
	}

	if (RunningProcess != nullptr && CurrentIO && RunningProcess->getCPUTime() - RunningProcess->getTimeCounter() == CurrentIO->RequestTime)//checks if it ran for the IO_R to add it to BLK list
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
	if (RunningProcess != nullptr && RunningProcess->getTimeCounter() != 0)  //Decrements the remaining time for process if it didnt finish its cpu time
	{
		RunningProcess->decrmntTimeCounter();
		ExpectedFinishTime--;

	}
	
	if (!RunningProcess && !RDY.isEmpty())//Adds new Process to RUN
	{
		RDY.deQueue(RunningProcess);
		RunningProcess->setState("RUN");
		RunningProcess->setRT(Time); //sets the Response time
		RunningProcess->getIORequests().peek(CurrentIO);
	}
	if (!RunningProcess) {
		IdleTime++; //Adds Idle time if there is no running process in the end of the algo
	}
	else {
		BusyTime++; //Adds Busy time if a process is currently running in the end of the algo
	}
}

void EDF::AddToRDY(Process* Prc)
{
	if (RunningProcess&&Prc->getDeadline() < RunningProcess->getDeadline()) //Checks if deadline of new process is smaller than running process
	{
		RDY.enQueue(RunningProcess, RunningProcess->getDeadline());//new process is queued into run and the old one is requeued to the rdy
		RunningProcess = Prc;
		addfinishtime(Prc);
	}
	else {

		RDY.enQueue(Prc, Prc->getDeadline()); // else proceed to enqueue normally
		addfinishtime(Prc);
	}
}

void EDF::Simulate()
{
}

void EDF::TerminateProcess(int randomnumber, int mode)
{
}

Process* EDF::StealProcess()
{
	Process* prc = nullptr;
	RDY.deQueue(prc);
	if (prc)
		ExpectedFinishTime -= prc->getTimeCounter();
	return prc;
}
void EDF::EmptyProcessor()
{
	if (RunningProcess)
	{
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
string EDF::getState()
{

	return State;

}

EDF::EDF(Scheduler* scheduler) // constructor that sets the scheduler pointer and processor type
{
	pScheduler = scheduler;
	Type = "EDF";
}

void EDF::PrintRDY()
{
	RDY.Print();
}

int EDF::getRDYCount()
{
	return RDY.getCount();
}

string EDF::getType()
{
	return Type;
}

void EDF::addfinishtime(Process* Prc) // Changes expected finish time of the processor
{
	ExpectedFinishTime += (Prc->getTimeCounter());
}

int EDF::getfinishtime() {
	return ExpectedFinishTime;
}
