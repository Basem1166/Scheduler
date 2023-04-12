#include "UI.h"

void UI::Interface(int TimeStep, Processor** ProcessorList, int ProcessorCount, Queue<Process*>* BLK, Queue<Process*>* TRM)
{
	int RDYCount, RUNCount=0;
	int y;
	cout << "Current Timestep: " << TimeStep << endl;
	cout << "-------------  RDY processes  -------------" << endl; //Ready Processes
	for (int i = 0; i < ProcessorCount; i++)
	{
		RDYCount = ProcessorList[i]->getRDYCount(); // the count of processes inside the RDY queue of each processor
		cout << "Processor " << i + 1 << " " << *ProcessorList[i] << " : "<<RDYCount<<" RDY: ";
		ProcessorList[i]->PrintRDY();
		cout << endl;
		
	}

	cout << "-------------  BLK processes  -------------" << endl; //Blocked processes
	cout << BLK->getCount() << " BLK: ";
	BLK->Print();
	cout << endl;


	cout << "-------------  RUN processes  -------------" << endl; //Running processes

	for (int i = 0; i < ProcessorCount; i++)// to get Running count
	{
		if (ProcessorList[i]->isRunning())
		{
			RUNCount++;
		}
	}

	cout << RUNCount << " RUN: ";
	bool first = true;
	for (int i = 0; i < ProcessorCount; i++)
	{
		if (ProcessorList[i]->isRunning())
		{
			if (first) {
				cout << *(ProcessorList[i]->getRunning()) << "(P" << i + 1 << ")";
				first = false;
			}
			cout <<", "<< *(ProcessorList[i]->getRunning()) << "(P" << i + 1 << ")";
		}
	}
	cout << endl;


	cout << "-------------  TRM processes  -------------" << endl; //Terminated processes
	cout << TRM->getCount() << " TRM: ";
	TRM->Print();
	cout << endl;

}

