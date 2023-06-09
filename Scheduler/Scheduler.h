#pragma once
#include<fstream>
#include<iostream>

#include"Queue.h"

#include"Processor.h"
#include"Process.h"

#include "RR.h"
#include "SJF.h"
#include "FCFS.h"
#include "EDF.h"

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
	Queue<SIGKILL> sigkill;
	Processor** ProcessorsList;
	int ProcessorCount;
	int OriginalProcessesCount;
	int Time;
	int NF;
	int NS;
	int NE;
	int M;
	int NR;
	int STL;
	int BeforeDLCount;
	int StolenProcesses;

public:

	Scheduler();
	void Simulate();
	void Read();
	void OutPut();
	void Execute();
	void InitializeProcessors();
	void AddtoTRM(Process*,int mode =0);
	void AddtoBLK(Process*);
	void CheckBLK();
	void CheckOrphan(Process* P);

	void WorkSteal();
	int getShortestFinishTime(int mode =0);
	int getLongestFinishTime();
	int getTotalBusyTime();
	void AddtoRDY(Process*, int mode=0);

	void Fork(Process*);


	bool Migrate(Process* P, int mode);


	int SigKill();


	~Scheduler();

};

