
#include "FCFS.h"

FCFS::FCFS(Scheduler* pSch)
{
	pScheduler = pSch;
	Type = "FCFS";
	ExpectedFinishTime = 0;
}

void FCFS::ScheduleAlgo(int Time)
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
	
	
	if (RunningProcess != nullptr && CurrentIO && RunningProcess->getCPUTime() - RunningProcess->getTimeCounter() == CurrentIO->RequestTime) //checks if it ran for the IO_R to add it to BLK list
	{
		pScheduler->AddtoBLK(RunningProcess);
		ExpectedFinishTime -= RunningProcess->getTimeCounter();
		RunningProcess = nullptr;
	}
	if (RunningProcess != nullptr && RunningProcess->getTimeCounter() != 0)   //Decrements the remaining time for process if it didnt finish its cpu time
	{
		RunningProcess->decrmntTimeCounter();
		ExpectedFinishTime--;
	}
	if (RunningProcess && RunningProcess->getTimeCounter() == 0)  //Terminates process if its finishes its cpu time
	{

		pScheduler->AddtoTRM(RunningProcess);
		RunningProcess = nullptr;

	}
	int pID = pScheduler->SigKill();
	while(pID!=-2) // to allow signal killing of 2 different processes at the same time
	{
		TerminateProcess(pID); //checks for sig kill  
		pID = pScheduler->SigKill();
	}
	

	while (!RunningProcess && !RDY.isEmpty())
	{
		RDY.Remove(1, RunningProcess);
		if (Time - RunningProcess-> getArrivalTime() > MaxW) // check if it should migrate or not
		{
			if (pScheduler->Migrate(RunningProcess, 2)) {           // call migrate function of the scheduler
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


	
	TempRandomNumber = generateRandomNumber(); //get a random number between 1 and 100
	if (RunningProcess&&TempRandomNumber < FCFS::getForkProb()) {
		pScheduler->Fork(RunningProcess);
		}
	if (!RunningProcess)
	{
		IdleTime++; //Adds Idle time if there is no running process in the end of the algo
	}
	else {
		BusyTime++; //Adds Busy time if a process is currently running in the end of the algo
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
		ExpectedFinishTime -= RunningProcess->getTimeCounter();
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
			ExpectedFinishTime -= Prc->getTimeCounter();
  			RDY.Remove(Prc);
			KilledProcesses++;
			
		}
	}
 	
	   


}

Process* FCFS::StealProcess() // returns the process to be stolen 
{
	Process* prc = nullptr; 
	prc = RDY.getEntry(1); // peeks the RDY
	if (prc && !prc->ischild() ) // checks if it exists and not a child 
	{
		RDY.Remove(1, prc); 
		ExpectedFinishTime -= prc->getTimeCounter();
		WorkStealingProcesses++;
		return prc;
	}
	else
	{
		return nullptr;
	}
	
	
	
}

//generic setter, getter and print functions 

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


string FCFS::getType()
{
	return Type;
}

int FCFS::getKilledProcessesNumber()
{
	return KilledProcesses;
}
//Static data members for all FCFS Processors
int FCFS::NumberOfProcesses = 0;
int FCFS::MigrationNumber = 0;
int FCFS::NumberOfMaxW;
int FCFS::ForkedProcesses = 0;
int FCFS::KilledProcesses = 0;
int FCFS::MaxW;
int FCFS::ForkProbability;//makes more sense to make them a static data member too
