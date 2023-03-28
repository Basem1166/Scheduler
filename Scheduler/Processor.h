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
public:
	virtual void ScheduleAlgo() = 0;
	void setState(string state);
};

