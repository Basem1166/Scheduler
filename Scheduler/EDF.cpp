#include "SJF.h"

void EDF::ScheduleAlgo()
{
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
	if (RunningProcess != nullptr)  // assuming TimesOfIO is RequestTime
	{
		RunningProcess->decrmntTimeCounter();
		ExpectedFinishTime--;

	}
	if (RunningProcess && RunningProcess->getTimeCounter() == 0)  //Terminates process if its finishes processing
	{
		RunningProcess->setTerminationT(pScheduler->getTime());
		RunningProcess->setTRT();
		pScheduler->AddtoTRM(RunningProcess);
		RunningProcess = nullptr;

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

void EDF::AddToRDY(Process* Prc)
{
	if (RunningProcess&&Prc->getDeadline() < RunningProcess->getDeadline()) {
		RDY.enQueue(RunningProcess, RunningProcess->getDeadline());
		RunningProcess = Prc;
		addfinishtime(Prc);
	}
	else {

		RDY.enQueue(Prc, Prc->getDeadline());
		addfinishtime(Prc);
	}
}

void EDF::Simulate()
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

EDF::EDF(Scheduler* scheduler)
{
	pScheduler = scheduler;
	Type = "SJF";
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

void EDF::addfinishtime(Process* Prc) {
	ExpectedFinishTime += (Prc->getTimeCounter());
}

int EDF::getfinishtime() {
	return ExpectedFinishTime;
}
int EDF::DeadlineCount=0;