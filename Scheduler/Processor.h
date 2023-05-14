#pragma once
#include <iostream>
#include "Process.h"
using namespace std;
class Scheduler;//forward declaration
class Processor
{
protected:
	static int WorkStealingProcesses;
	static int OverHeatTime;
	int OverHeatCounter;
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
	virtual Process* StealProcess() = 0;
	virtual int getfinishtime() = 0;
	virtual int generateRandomNumber();
	virtual void TerminateProcess(int,int mode =0)=0;
	virtual void EmptyProcessor()=0;
	virtual string getType() = 0;
	virtual string getState() = 0;
	static void setOverHeatTime(int OverHeatTime);
	friend ostream& operator<<(ostream& os, const Processor& processor);
	void OverHeat();
	int generateRandomNumber1000();
	bool isRunning();
	void PrintRunning();
	int getBusyTime();
	Processor();
};

