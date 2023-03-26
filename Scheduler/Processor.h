#pragma once
#include <iostream>
using namespace std;

class Processor
{
private:
	string State;
	int ExpectedFinishTime;
public:
	virtual void ScheduleAlgo() = 0;
	void setState(string state);
};

