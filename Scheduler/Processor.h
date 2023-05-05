#pragma once
#include <iostream>
#include "Process.h"
using namespace std;
class Scheduler;//forward declaration
class Processor
{
protected:
	static int WorkStealingProcesses;
	Process* RunningProcess = nullptr;
	string State;
	string Type;
	int ExpectedFinishTime;
	int IdleTime=0; // total idle time of processor
	int BusyTime=0;
	
public:
	virtual void ScheduleAlgo() = 0;
	virtual void Simulate() = 0;
	virtual void setState(string state);
	virtual void AddToRDY(Process* Prc) = 0;
	virtual void PrintRDY() = 0;
	virtual int getRDYCount() = 0;
	virtual void addfinishtime(Process* Prc) = 0;
	virtual int getfinishtime() = 0;
	virtual int generateRandomNumber();
	virtual void TerminateProcess(int)=0;
	friend ostream& operator<<(ostream& os, const Processor& processor);
	bool isRunning();
	void PrintRunning();
	Processor();
};

