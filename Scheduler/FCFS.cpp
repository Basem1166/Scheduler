
#include "FCFS.h"

FCFS::FCFS(Scheduler* pSch)
{
	pScheduler = pSch;
	Type = "FCFS";
}

void FCFS::ScheduleAlgo()
{
	OverHeat();
	if (State == "STOP")
	{
		return;
	} 
	

	int TempRandomNumber;
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
		//RunningProcess->setTRT();


		pScheduler->AddtoTRM(RunningProcess);
		RunningProcess = nullptr;

	}

	int pID = pScheduler->SigKill();
	TerminateProcess(pID); //checks for sig kill  

	while (!RunningProcess && !RDY.isEmpty())
	{
		RDY.Remove(1, RunningProcess);
		if (RunningProcess->getCPUTime() + getReadyWaitTime() > MaxW) // check if it should migrate or not
		{
			if (pScheduler->Migrate(RunningProcess, 2)) {           // call migrate function of the scheduler
				MigrationNumber++;
				RunningProcess = nullptr;
				continue;
			}
		}
		RunningProcess->setState("RUN");
		RunningProcess->setRT(pScheduler->getTime()); //need to set arrival time in execute
		RunningProcess->getIORequests().peek(CurrentIO);


		if (!RunningProcess) {
			IdleTime++;
		}
		else {
			BusyTime++;
		}

	}
	
	TempRandomNumber = generateRandomNumber(); //get a random number between 1 and 100
	if (RunningProcess&&TempRandomNumber < FCFS::getForkProb()) {
		pScheduler->Fork(RunningProcess);
		}
	}

void FCFS::Simulate() {}

void FCFS::AddToRDY(Process* Prc)
{
	RDY.InsertEnd(Prc); 
	addfinishtime(Prc);
	

}
//mode = 0 -> Normal Process
//mode = 1 -> Forked Process
void FCFS::TerminateProcess(int pID,int mode)
{
	if (pID == -2)
		return;
	if (RunningProcess && pID == RunningProcess->getProcessID()) {
		pScheduler->AddtoTRM(RunningProcess,mode);
		KilledProcesses++;
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
			pScheduler->AddtoTRM(Prc,mode);
  			RDY.Remove(Prc);
			
		}
	}
 	
	   


}

Process* FCFS::StealProcess()
{
	Process* prc = nullptr; 
	prc = RDY.getEntry(1);
	if (prc && !prc->ischild() )
	{
		RDY.Remove(1, prc);
		ExpectedFinishTime -= prc->getCPUTime();
		WorkStealingProcesses++;
		return prc;
	}
	else
	{
		return nullptr;
	}
	
	
	
}



void FCFS::setMaxW(int maxW)
{
	MaxW = maxW;
}
void FCFS::EmptyProcessor() {

	if (RunningProcess) {
		pScheduler->AddtoRDY(RunningProcess);
		RunningProcess = nullptr;
	}
	Process* prc;
	while (!RDY.isEmpty())
	{
		RDY.Remove(1, prc);
		if (prc->ischild())
		{
			pScheduler->AddtoRDY(prc,3);
		}
		pScheduler->AddtoRDY(prc);
	}

}
string FCFS::getState() {

	return State;

}

void FCFS::setForkProb(int Prob)
{
	ForkProbability = Prob;
}
int FCFS::getForkProb() {
	return ForkProbability;
}

void FCFS::IncrementMigrationNumber()
{
	MigrationNumber++;
}

int FCFS::getMigrationNumber()
{
	return MigrationNumber;
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
	ExpectedFinishTime += (Prc->getTimeCounter());
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

string FCFS::getType()
{
	return Type;
}

int FCFS::getKilledProcessesNumber()
{
	return KilledProcesses;
}

int FCFS::NumberOfProcesses = 0;
int FCFS::MigrationNumber = 0;
int FCFS::NumberOfMaxW;
int FCFS::ForkedProcesses = 0;
int FCFS::KilledProcesses = 0;
int FCFS::MaxW;
int FCFS::ForkProbability;//makes more sense to make them a static data member too
