#include "Processor.h"
#include <random>

void Processor::setState(string state)
{
	State = state;
}

int Processor::generateRandomNumber()
{
	

	return rand() % 100 + 1; // generate a random number between 1 and 100
}
int Processor::generateRandomNumber1000()
{


	return rand() % 1000 + 1; // generate a random number between 1 and 100
}


bool Processor::isRunning()
{
	if(RunningProcess != nullptr)
	{
		return true;
	}
	return false;
}

void Processor::PrintRunning()
{
	cout<<*RunningProcess;
}

Processor::Processor()
{
	srand(time(NULL)); // seed the random number generator with the current time
	State = "IDLE";
	IdleTime = 0; //initializing idletime to zero
	ExpectedFinishTime = 0;
	RunningProcess = nullptr; //?? add or is state sufficient "TO BE EDITED"
}



ostream& operator<<(ostream& os, const Processor& processor)
{
	os << "[ " << processor.Type << " ]";
	return os;}

void Processor::setOverHeatTime(int overheattime)
{
	OverHeatTime = overheattime;
}

void Processor::OverHeat() {

	if (State=="STOP")
	{
		OverHeatCounter--;
		if (OverHeatCounter==0)
		{
			State = "IDLE";
			return;
		}
	}

	if (State != "STOP") {   
		int randomNumber = generateRandomNumber1000();
		if (randomNumber == 420 )
		{
			State = "STOP";
			ExpectedFinishTime = 0;
			EmptyProcessor();
		}
		OverHeatCounter = OverHeatTime;
	}
	

}


int Processor::getBusyTime()
{
	return BusyTime;
}

int Processor::getIdleTime()
{
	return BusyTime;
}

int Processor::WorkStealingProcesses=0;
int Processor::OverHeatTime;
