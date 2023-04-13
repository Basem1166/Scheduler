
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
	if (State == "IDLE" && !RDY.isEmpty()) {
		
		RDY.Remove(1,RunningProcess);
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
	}
}

void FCFS::AddToRDY(Process* Prc)
{
	RDY.InsertEnd(Prc);

}

void FCFS::TerminateRandomProcess()
{
	if (RDY.isEmpty())
		return;
	Process* Prc;
	int RandomNumber = rand() % RDY.getLength()+1 ; // Generate the number, assign to variable.           
 	RDY.Remove(RandomNumber, Prc);
	pScheduler->AddtoTRM(Prc);
	   


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
