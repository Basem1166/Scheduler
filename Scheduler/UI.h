#pragma once
#include"Scheduler.h"

class UI
{
public:
	void Interface(int TimeStep, Processor** ProcessorList, int ProcessorCount, Queue<Process*>* BLK, Queue<Process*>* TRM, int mode=0);

	int Mode();

	void Output();

};



