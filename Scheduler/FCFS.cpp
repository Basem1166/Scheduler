
#include "FCFS.h"

FCFS::FCFS(Scheduler* pSch)
{
	pScheduler = pSch;
	Type = "FCFS";
}

void FCFS::ScheduleAlgo()
{
	IORequests* CurrentIO = nullptr; // TO BE ABLE TO PEAK/DEQUEUE FROM THE IO QUEUE
	int pID = pScheduler->SigKill();
	TerminateProcess(pID); //checks for sig kill
	if (RunningProcess != nullptr && RunningProcess->getCPUTime() - RunningProcess->getTimeCounter() != CurrentIO->RequestTime)  // assuming TimesOfIO is RequestTime
	{
		RunningProcess->decrmntTimeCounter();
	}
	if (RunningProcess != nullptr && RunningProcess->getCPUTime() - RunningProcess->getTimeCounter() == CurrentIO->RequestTime)
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
	while (!RunningProcess && !RDY.isEmpty())
	{
		RDY.Remove(1, RunningProcess);
		if (RunningProcess->getCPUTime() + getReadyWaitTime() > MaxW) // check if it should migrate or not
		{
			// call migrate function of the scheduler (will probably pass the Running process to it)
			RunningProcess = nullptr;
			continue;
		}
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

void FCFS::Simulate() {}

void FCFS::AddToRDY(Process* Prc)
{
	RDY.InsertEnd(Prc); 

}

void FCFS::TerminateProcess(int pID)
{
	if (pID == -1)
		return;
	if (pID == RunningProcess->getProcessID()) {
		pScheduler->AddtoTRM(RunningProcess);
		RunningProcess = nullptr;
	}
	if (RDY.isEmpty())
		return;
	Process* Prc;
	for (int i = 1; i < RDY.getLength()+1; i++) // loop over rdy list 
	{
		if (RDY.getEntry(i)->getProcessID()==pID) //check if random number = process ID 
		{
			Prc = RDY.getEntry(i);
			pScheduler->AddtoTRM(Prc);
  			RDY.Remove(Prc);
			
		}
	}
 	
	   


}

Process* FCFS::StealProcess()
{
	Process* prc;
	RDY.Remove(1, prc);
	ExpectedFinishTime -= prc->getCPUTime();
	return prc;
	
	
}



void FCFS::setMaxW(int maxW)
{
	MaxW = maxW;
}

void FCFS::setForkProb(int Prob)
{
	ForkProbability = Prob;
}

void FCFS::PrintRDY()
{
	RDY.Print();
}

int FCFS::getRDYCount()
{
	return RDY.getLength();
}

void FCFS::addfinishtime(Process* Prc) {
	ExpectedFinishTime += (Prc->getCPUTime());
}

int FCFS::getfinishtime() {
	return ExpectedFinishTime;
}

int FCFS::getReadyWaitTime()
{
	Process* P;
	int count = getRDYCount(), Wait = 0;
	for (int i = 1; i <= count; i++)
	{
		P = RDY.getEntry(i);
		Wait += P->getCPUTime();
	}

	return Wait;
}

int FCFS::NumberOfProcesses;
int FCFS::NumberOfMaxW;
int FCFS::ForkedProcesses;
int FCFS::KilledProcesses;
int FCFS::MaxW;
int FCFS::ForkProbability;//makes more sense to make them a static data member too
