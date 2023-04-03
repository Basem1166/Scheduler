#include "Scheduler.h"

Scheduler::Scheduler()
{
	Read();
	Time = 0;
	ProcessorCount = 0;
	ProcessorsList = new Processor * [NF + NR + NS];
	for (int i = 0; i < NF + NR + NS; i++) {
		ProcessorsList[i] = nullptr;
	}
	InitializeProcessors();


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
		fin >> NF >> NS >> NR >> TimeSliceOfRR >> RTF >> MaxW >>STL>>ForkProb>> M; // Inputs the necessary data from the input file to the variables
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

		for (int i = 0; i < 12; i++)// Ignores the Word SIGKILL TIMES 
		{
			fin >> temp;
		}
		
		int a, b;
		while (fin >> a >> b) { // read each integer pair until the end of the file
			sigkill.push_back(SIGKILL(a, b)); // create a SIGKILL object and add it to the vector
		}

	}
	fin.close(); //closes the file after usage

}

void Scheduler::Execute()
{
	Process* Prc;
	int ProcessorAddCounter = 0;

	while (Time<1000)//Temporary condition to test, this is the while for every timestep , the end condition would be in this while.
	{
		Time++;//Increments the time 

/////////////////////////////////////////////////////////////////////////////////////////////////////
		//Adding the arrived Processes to the processors.
		while (true) {

			NEW.peek(Prc);
			if (Prc->getArrivalTime() == Time)//checks to see if the process is now in its arrival time;
			{
				ProcessorsList[ProcessorAddCounter]->AddToRDY(Prc);//Add To the current process
				NEW.deQueue(Prc);//remove from new list
				ProcessorAddCounter++;
				if (ProcessorAddCounter == ProcessorCount)
					ProcessorAddCounter = 0;
				if (NEW.isEmpty())
					break;
			}
			else
			{
				break;
			}
///////////////////////////////////////////////////////////////////////////////////////////////////////



		}

	}
}
int Scheduler::getTime() {
	return Time;
}

int Scheduler::getTimeSlice()
{
	return TimeSliceOfRR;
}

void Scheduler::InitializeProcessors()
{
	Processor* P;
	for (int i = 0; i < NR; i++)
	{
	    P = new RR(this);
		ProcessorsList[ProcessorCount] = P;
		ProcessorCount++;
	}
	for (int i = 0; i < NS; i++)
	{
		P = new SJF(this);
		ProcessorsList[ProcessorCount++] = P;

	}
	for (int i = 0; i < NF; i++)
	{
		P = new FCFS;
		ProcessorsList[ProcessorCount++] = P;
	}
}

void Scheduler::AddtoTRM(Process* P)
{
	TRM.enQueue(P);
 
}

void Scheduler::AddtoBLK(Process* P)
{
	BLK.enQueue(P);
}

void Scheduler::AddtoORPH(Process* P)
{
	ORPH.enQueue(P);
}

Scheduler::~Scheduler()
{
	for (int i = 0; i < ProcessorCount; i++) {
		delete ProcessorsList[i];
	}
	delete[] ProcessorsList;
}

