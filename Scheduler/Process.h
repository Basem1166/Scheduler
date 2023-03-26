#pragma once
#include "IORequests.h"
#include <iostream>
using namespace std;

class Process
{
private:
	int ProcessID;
	int ArrivalTime;
	int CPUTime;
	int TimesOfIO;
	//will be set during Runtime

	int TerminationTime;
	int TurnAroundDuration;
	int ResponseTime;
	int WaitingTime;
	
	//////////////////////////////////////////////////

	IORequests** IoRequests;// could be queue?
	string State;
	string Type;
public:
	Process(int pid, int at, int ct, int toi, IORequests ior[]);
	//Setters




	//Getters
	int getProcessID();
	int getArrivalTime();
	int getCPUTime();
	int getTimesOfIO();
	IORequests** getIORequests();
};

