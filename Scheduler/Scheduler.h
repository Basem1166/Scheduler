#pragma once
#include<fstream>
#include<iostream>

#include"Queue.h"

#include"Processor.h"
#include"Process.h"

using namespace std;
class Scheduler
{
private:
	Queue<Process*> NEW;
	Processor** ProcessorsList;
	int ProcessorCount;
	int Time;
	int NF;
	int NS;
	int TimeSliceOfRR;
	int RTF;
	int MaxW;
	int M;
	int NR;

public:

	Scheduler();
	void Read();
	void Execute();
	void Initialize();
};

