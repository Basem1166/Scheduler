
#include "FCFS.h"

FCFS::FCFS(Scheduler* pSch)
{
	pScheduler = pSch;
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
	int x = generateRandomNumber();
	if (x >= 1 && x <= 15) {
		pScheduler->AddtoBLK(RunningProcess);
		State = "IDLE";
	}
	else if (x >= 20 && x <= 30) {
		AddToRDY(RunningProcess);
		State = "IDLE";
	}
	else if (x >= 50 && x <= 60) {
		pScheduler->AddtoTRM(RunningProcess);
		State = "IDLE";
	}
}

void FCFS::AddToRDY(Process* Prc)
{
	RDY.InsertEnd(Prc);

}

void FCFS::TerminateRandomProcess()
{
	Process* Prc;
	srand(time(NULL)); // Seed the time
	int RandomNumber = rand() % (RDY.getLength() + 1); // Generate the number, assign to variable.
	RDY.Remove(RandomNumber, Prc);
	pScheduler->AddtoTRM(Prc);
	   


}
