#include "SJF.h"

void SJF::ScheduleAlgo()
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
	
	if (RunningProcess != nullptr && CurrentIO && RunningProcess->getCPUTime() - RunningProcess->getTimeCounter() == CurrentIO->RequestTime)
	{
		pScheduler->AddtoBLK(RunningProcess);
		ExpectedFinishTime -= RunningProcess->getTimeCounter();
		RunningProcess = nullptr;
	}
	
	if (RunningProcess && RunningProcess->getTimeCounter() == 0)  //Terminates process if its finishes processing
	{
		//RunningProcess->setTRT();

		pScheduler->AddtoTRM(RunningProcess);
		RunningProcess = nullptr;

	}
	if (RunningProcess != nullptr)  // assuming TimesOfIO is RequestTime
	{
		RunningProcess->decrmntTimeCounter();
		ExpectedFinishTime--;

	}
	if (!RunningProcess && !RDY.isEmpty())
	{
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

void SJF::AddToRDY(Process* Prc)
{
	RDY.enQueue(Prc, Prc->getCPUTime());
	addfinishtime(Prc);
}

void SJF::Simulate()
{
/**if (State == "IDLE" && !RDY.isEmpty()) {

		RDY.deQueue(RunningProcess);
		State = "BUSY";
	}

	if (!RunningProcess)
		return;
	int x = generateRandomNumber();
	if (x >= 1 && x <= 15) {
		pScheduler->AddtoBLK(RunningProcess);
		State = "IDLE";
		RunningProcess = nullptr;
	}
	else if (x >= 20 && x <= 30) {
		AddToRDY(RunningProcess);
		State = "IDLE";
		RunningProcess = nullptr;
	}
	else if (x >= 50 && x <= 60) {
		pScheduler->AddtoTRM(RunningProcess);
		State = "IDLE";
		RunningProcess = nullptr;
	}*/
}

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

 };
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
