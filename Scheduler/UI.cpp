#include "UI.h"

void UI::Interface(int TimeStep, Processor** ProcessorList, int ProcessorCount)
{
	int RDYCount;
	int y;
	cout << "Current Timestep: " << TimeStep << endl;
	cout << "-------------  RDY processes  -------------" << endl;
	for (size_t i = 0; i < ProcessorCount; i++)
	{
		RDYCount = ProcessorList[i]->getRDYCount(); // the count of processes inside the RDY queue of each processor
		cout << "Processor " << i + 1 << " " << *ProcessorList[i] << " : "<<RDYCount<<" RDY: ";
		ProcessorList[i]->PrintRDY();
		cout << endl;
		
		
	}

}

