#include "Scheduler.h"

void Scheduler::Read(int& NF, int& NS, int& NR, int& RR, int& RTF, int& MaxW, int& M)
{
	// Variables to be used when creating new processes
	int AT;
	int pID;
	int CT;
	int N;
	int IO_R;
	int IO_D;
	char temp = ' ';

	ifstream fin("Input.txt", ios::in); //Creates an fstream object and opens the input file\

	if (!fin.is_open()) //checks if the file didn't open properly
	{
		cout << "Error openning the file please check the file location";

	}
	else
	{
		fin >> NF >> NS >> NR >> RR >> RTF >> MaxW >> M; // Inputs the necessary data from the input file to the variables
		for (int i = 0; i < M; i++)
		{
			fin >> AT >> pID >> CT >> N;

			IORequests*ior = new IORequests[N]; //there might be a memory leak in the future here (need to delete it somehow after using it)

			for (int j = 0; j < N; j++)
			{
				
				
				fin >>temp>> IO_R>>temp>>IO_D>>temp;
				ior[j] = IORequests(IO_R, IO_D);
				if (j != N - 1) 
				{
					fin >> temp;
				}
					
				

				
			}
			Process* temp = new Process(AT, pID, CT, N, ior);
			NEW.enQueue(temp);
			
		}
	}

}
