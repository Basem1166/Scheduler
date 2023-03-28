#pragma once
#include<fstream>
#include<iostream>

#include"Queue.h"
#include"pQueue.h"
#include"Processor.h"
#include"Process.h"

using namespace std;
class Scheduler
{
private:
	Queue<Process*> NEW;
	Queue<Processor*> ProcessorsList;
	int Time;
	int NF;
	int NS;
	int RR;
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

