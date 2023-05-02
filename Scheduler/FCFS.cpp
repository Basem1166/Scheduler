
#include "FCFS.h"

FCFS::FCFS(Scheduler* pSch)
{
	pScheduler = pSch;
	Type = "FCFS";
}

void FCFS::ScheduleAlgo()
{
	IORequests* CurrentIO = nullptr; // TO BE ABLE TO PEAK/DEQUEUE FROM THE IO QUEUE
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
	if (!RunningProcess && !RDY.isEmpty())
	{
		RDY.Remove(1,RunningProcess);
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

void FCFS::TerminateRandomProcess(int randomnumber)
{
	if (RDY.isEmpty())
		return;
	Process* Prc;
	for (int i = 1; i < RDY.getLength()+1; i++) // loop over rdy list 
	{
		if (RDY.getEntry(i)->getProcessID()==randomnumber) //check if random number = process ID 
		{
			Prc = RDY.getEntry(i);
			pScheduler->AddtoTRM(Prc);
  			RDY.Remove(Prc);
			
		}
	}
 	
	   


}

void FCFS::setMaxW(int maxW)
{
	MaxW = maxW;
}

void FCFS::setForkProb(int Prob)
{
	ForkProbability = Prob;
}

void FCFS::AddSigKill(SIGKILL s)
{
	SigKill.enQueue(s);
}

void FCFS::PrintRDY()
{
	RDY.Print();
}

int FCFS::getRDYCount()
{
	return RDY.getLength();
}

int FCFS::NumberOfProcesses;
int FCFS::NumberOfMaxW;
int FCFS::ForkedProcesses;
int FCFS::KilledProcesses;
int FCFS::MaxW;
int FCFS::ForkProbability;//makes more sense to make them a static data member too

Queue<SIGKILL> FCFS::SigKill;
