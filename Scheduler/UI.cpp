#include "UI.h"
#include <windows.h>   

void UI::Interface(int TimeStep, Processor** ProcessorList, int ProcessorCount, Queue<Process*>* BLK, Queue<Process*>* TRM, int mode)
{
	int RDYCount, RUNCount=0;
	int y;
	
	

	if (mode != 3)
	{
		cout << "Current Timestep: " << TimeStep << endl;
		cout << "-------------  RDY processes  -------------" << endl; //Ready Processes
		for (int i = 0; i < ProcessorCount; i++) // loops over the processor list and calls the print function in each Processor
		{
			RDYCount = ProcessorList[i]->getRDYCount(); // the count of processes inside the RDY queue of each processor
			cout << "Processor " << i + 1 << " " << *ProcessorList[i] << " : " << RDYCount << " RDY: ";
			ProcessorList[i]->PrintRDY();
			if (ProcessorList[i]->getState()=="STOP")
			{
				cout << "OVERHEATED!!!"; 
			}
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
					ProcessorList[i]->PrintRunning();
					cout << "(P" << i + 1 << ")";
					first = false;
					continue;
				}
				cout << ", ";
				ProcessorList[i]->PrintRunning();
				cout << "(P" << i + 1 << ")";
			}
		}
		cout << endl;


		cout << "-------------  TRM processes  -------------" << endl; //Terminated processes
		cout << TRM->getCount() << " TRM: ";
		TRM->Print();
		cout << endl;

		if (mode == 1)
		{
			system("pause");
		}
		else if (mode == 2)
		{
			Sleep(1000);
		}
	}
	else
	{
		system("cls");
		cout << "Silent Mode,,,,,,	Simulation Starts....." << endl << "Simulation Ends, Output File Created" << endl;
	}
	

}

int UI::Mode()
{
	int mode = 0;

	cout << "Choose which mode you want:" << endl << "1-Interactive Mode" << endl << "2-Step-By-Step Mode" << endl << "3-Silent Mode" << endl;
	while (!(mode >= 1 && mode <= 3))
	{
		cin >> mode;

		if (!(mode >= 1 && mode <= 3))
		{
			cout << "not an available mode please enter a number from 1-3" << endl;
		}
	}
	return mode;
}


