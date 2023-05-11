#pragma once
#include "IORequests.h"
#include <iostream>
#include "Queue.h"
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
	int TimeCounter; //to get the remaining time for each process
	bool isChild;
	bool isParent;
	Process* Child;

	
	//////////////////////////////////////////////////
	Queue<IORequests*> IoRequests;// could be queue?
	string State;
	string Type;
public:
	Process(int at, int pid, int ct, int toi, IORequests ior[]);
	//Setters
	void setState(string);
	void setArrivalTime(int);
	void setCPUTime(int);
	void setTerminationT(int);
	void setTRT();
	void setWT(int);
	void setRT(int);
	void decrmntTimeCounter();
	IORequests* getIORequest();
	void RemoveIORequest();
	bool checkIORequestDurationTime();
	void setchild(Process*);
	bool ischild();
	bool isparent();
	int getChildID();
	//Getters
	int getProcessID();
	int getArrivalTime();
	int getCPUTime();
	int getTimesOfIO();
	int getTerminationTime();
	int getTimeCounter(); //The timesteps remaining of running process
	Queue<IORequests*> getIORequests();

	friend ostream& operator<<(ostream& os, const Process& process);



};

