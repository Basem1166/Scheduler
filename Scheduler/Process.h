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
	int TimeCounter = CPUTime;
	
	//////////////////////////////////////////////////

	IORequests* IoRequests;// could be queue?
	/*string State;
	string Type;*/
public:
	Process(int at, int pid, int ct, int toi, IORequests ior[]);
	//Setters
	void setArrivalTime(int);
	void setCPUTime(int);
	void setTerminationT(int);
	void setTRT(int);
	void setWT(int);
	void setRT(int);
	void decrmntTimeCounter();

	//Getters
	int getProcessID();
	int getArrivalTime();
	int getCPUTime();
	int getTimesOfIO();
	int getTerminationTime();
	int getTimeCounter();
	IORequests* getIORequests();
};

