#pragma once
#include <iostream>
#include "Process.h"
using namespace std;

class Processor
{
protected:
	Process* RunningProcess;
	string State;
	int ExpectedFinishTime;
	int IdleTime;
public:
	virtual void ScheduleAlgo() = 0;
	virtual void setState(string state);
	virtual void AddToRDY(Process* Prc) = 0;
	Processor();
};

