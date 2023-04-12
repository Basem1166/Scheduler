#pragma once
#include<fstream>
#include<iostream>

#include"Queue.h"

#include"Processor.h"
#include"Process.h"

#include "RR.h"
#include "SJF.h"
#include "FCFS.h"

#include "SIGKILL.h"

#include"UI.h"

using namespace std;

class Scheduler
{
private:
	Queue<Process*> NEW;
	Queue<Process*> TRM;
	Queue<Process*> BLK;
	Queue<Process*> ORPH;
	Processor** ProcessorsList;
	int ProcessorCount;
	int Time;
	int NF;
	int NS;
	int M;
	int NR;
	int STL;
	vector<SIGKILL> sigkill;

public:

	Scheduler();
	int getTime();
	int getTimeSlice();
	void Simulate();
	void Read();
	void Execute();
	void InitializeProcessors();
	void AddtoTRM(Process*);
	void AddtoBLK(Process*);
	void AddtoORPH(Process*);

	~Scheduler();

};

