#pragma once
#include <iostream>
#include "Process.h"
using namespace std;
class Scheduler;//forward declaration
class Processor
{
protected:
	static int WorkStealingProcesses;
	Process* RunningProcess;
	string State;
	string Type;
	int ExpectedFinishTime;
	int IdleTime; // total idle time of processor
	int BusyTime;
	
public:
	virtual void ScheduleAlgo() = 0;
	virtual void Simulate() = 0;
	virtual void setState(string state);
	virtual void AddToRDY(Process* Prc) = 0;
	virtual void PrintRDY() = 0;
	virtual int getRDYCount() = 0;
	virtual int generateRandomNumber();
	virtual void TerminateRandomProcess()=0;
	friend ostream& operator<<(ostream& os, const Processor& processor);
	bool isRunning();
	Process* getRunning();
	Processor();
};

