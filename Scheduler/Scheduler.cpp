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

			for (int i = 0; i < N; i++)
			{
				//fin.ignore(1, '('); // ignores the opening bracket before reading the Request time
				fin >> IO_R;

				//fin.ignore(1, ',');
				fin >> IO_D;

				//fin.ignore(1, ')');// ignores the Closing brackets after reading the Duration
				//fin.ignore(1, ',');

				ior[i] = IORequests(IO_R, IO_D);
			}
			Process* temp = new Process(AT, pID, CT, N, ior);
			NEW.enQueue(temp);
			
		}
	}

}
