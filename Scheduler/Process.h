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
	int Deadline;
	bool RTCheck;
	//////////////////////////////////////////////////
	Queue<IORequests*> IoRequests;// could be queue?
	Queue<IORequests*> UsedIoRequests;
	string State;
	string Type;
public:
	Process(int at, int pid, int ct,int deadline, int toi, IORequests ior[]);
	//Setters
	void setState(string);
	void setRTCheck(bool);
	void setArrivalTime(int);
	void setCPUTime(int);
	void setTerminationT(int);
	void setTRT();
	void setWT();
	int getWT();
	void setRT(int);
	int getRT();
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
	bool getRTCheck();
	int getArrivalTime();
	int getCPUTime();
	int getIO_D();
	int getTimesOfIO();
	int getTerminationTime();
	int getTimeCounter(); //The timesteps remaining of running process
	Queue<IORequests*> getIORequests();

	friend ostream& operator<<(ostream& os, const Process& process);
	int getDeadline();
	


};

