#include "Scheduler.h"

Scheduler::Scheduler()
{
	Time = 0;
}

void Scheduler::Read()
{
	// Variables to be used when creating new processes
	int AT;
	int pID;
	int CT;
	int N;
	int IO_R;
	int IO_D;
	char temp = ' '; // character used to temporarily store the brackets and commas+
	

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

			for (int j = 0; j < N; j++) // loops over the number of brackets containing the Values of IO_R and IO_D and extracts them
			{
				
				
				fin >>temp>> IO_R>>temp>>IO_D>>temp;
				ior[j] = IORequests(IO_R, IO_D); // Stores the IO_R and IO_D inside the ior array
				if (j != N - 1) // Checks if there's a comma between the brackets
				{
					fin >> temp; //stores the brackets when needed
				}
				
				

				
			}
			Process* temp = new Process(AT, pID, CT, N, ior); //creates a new process after reading each line
			NEW.enQueue(temp); //Stores each new process inside the scheduler's NEW Queue
			
		}
	}
	fin.close(); //closes the file after usage

}

void Scheduler::Execute()
{
	while (true)
	{
		




	}
}

void Scheduler::Initialize()
{
	for (int i = 0; i < NR; i++)
	{

	}
	for (int i = 0; i < NS; i++)
	{

	}
	for (int i = 0; i < NF; i++)
	{

	}
}

