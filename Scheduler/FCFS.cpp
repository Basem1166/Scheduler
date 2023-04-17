
#include "FCFS.h"

FCFS::FCFS(Scheduler* pSch)
{
	pScheduler = pSch;
	Type = "FCFS";
}

void FCFS::ScheduleAlgo()
{
}

void FCFS::Simulate()
{
	if (State == "IDLE" && !RDY.isEmpty()) //see if processor is idle and rdy is not empty 
	{
		
		RDY.Remove(1,RunningProcess); //remove first element of rdy 
		State = "BUSY"; // set processor to busy
	}
	
	if (!RunningProcess) // see if processor is idle 
		return;
	int x = generateRandomNumber(); // generate a random number 
	if (x >= 1 && x <= 15) {
		pScheduler->AddtoBLK(RunningProcess); //add to blk 
		State = "IDLE"; 
		RunningProcess = nullptr;
	}
	else if (x >= 20 && x <= 30) {
		AddToRDY(RunningProcess); // add to rdy 
		State = "IDLE";
		RunningProcess = nullptr;
	}
	else if (x >= 50 && x <= 60) {
		pScheduler->AddtoTRM(RunningProcess); // add to trm 
		State = "IDLE";
		RunningProcess = nullptr;
	}
}

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
