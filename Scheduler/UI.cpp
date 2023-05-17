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

		cout << RUNCount << " RUN: "; //Running Count
		bool first = true;
		for (int i = 0; i < ProcessorCount; i++)
		{
			if (ProcessorList[i]->isRunning())
			{
				if (first) {
					ProcessorList[i]->PrintRunning();
					cout << "(P" << i + 1 << ")"; //Prints processor number
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

		if (mode == 1) //mode 1 is interactive mode so you have to press for the next timestep
		{
			system("pause");
		}
		else if (mode == 2) //mode 2 is step by step mode so it will wait one second to display the next time step
		{
			Sleep(1000);
		}
	}
	else // mode 3 is the silent mode
	{
	
		system("cls");

		cout << "S"; 
		Sleep(50);
		cout << "i";
		Sleep(50);
		cout << "l";
		Sleep(50);
		cout << "e";
		Sleep(50);
		cout << "n";
		Sleep(50);
		cout << "t";

		cout << " ";
		Sleep(100);

		cout << "M";
		Sleep(50);
		cout << "o";
		Sleep(50);
		cout << "d";
		Sleep(50);
		cout << "e";
		Sleep(50);

		for (size_t i = 0; i < 5; i++)
		{
			cout << ",";
			Sleep(250);
		}
		

		cout << "S";
		Sleep(50);
		cout << "i";
		Sleep(50);
		cout << "m";
		Sleep(50);
		cout << "u";
		Sleep(50);
		cout << "l";
		Sleep(50);
		cout << "a";
		Sleep(50);
		cout << "t";
		Sleep(50);
		cout << "i";
		Sleep(50);
		cout << "o";
		Sleep(50);
		cout << "n";
		Sleep(50);

		cout << " ";
		Sleep(100);

		cout << "S";
		Sleep(50);
		cout << "t";
		Sleep(50);
		cout << "a";
		Sleep(50);
		cout << "r";
		Sleep(50);
		cout << "t";
		Sleep(50);
		cout << "s";
		Sleep(50);



		for (size_t i = 0; i < 5; i++)
		{
			cout << ".";
			Sleep(250);
		}
		Sleep(300);
		cout << endl;

		
	}
	

}

int UI::Mode() //this function gets called at the beggining to let the user choose the mode they like
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



void UI::OutputFinished() //gets called after the output file is created
{
	cout << "Simulation Ends, Output File Created" << endl;
}


