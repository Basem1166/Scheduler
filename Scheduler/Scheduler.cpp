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
	srand(time(NULL)); // seed the random number generator with the current time


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

	int RTF, MaxW, ForkProbability, TimeSliceOfRR;
	

	ifstream fin("Input.txt", ios::in); //Creates an fstream object and opens the input file\

	if (!fin.is_open()) //checks if the file didn't open properly
	{
		cout << "Error openning the file please check the file location";

	}
	else
	{
		fin >> NF >> NS >> NR >> TimeSliceOfRR >> RTF >> MaxW >> STL >> ForkProbability >> M; // Inputs the necessary data from the input file to the variables

		RR::setRTF(RTF);
		RR::setTimeSlice(TimeSliceOfRR);
		FCFS::setMaxW(MaxW);
		FCFS::setForkProb(ForkProbability); //Sets Static members necessary

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
			sigkill.enQueue(SIGKILL(a, b)); // create a SIGKILL object and add it to the vector
		}

	}
	fin.close(); //closes the file after usage

}

void Scheduler::Execute() // not used in phase 1
{

	Process* Prc;
	int TempRandomNumber;

	while (TRM.getCount() != M)//Temporary condition to test, this is the while for every timestep , the end condition would be in this while.
	{
		Time++;//Increments the time 

		/////////////////////////////////////////////////////////////////////////////////////////////////////
				//Adding the arrived Processes to the processors.
		while (true) {

			NEW.peek(Prc);
			if (Prc->getArrivalTime() == Time)//checks to see if the process is now in its arrival time;
			{
				AddtoRDY(Prc);
				NEW.deQueue(Prc);//remove from new list
				
				if (NEW.isEmpty())
					break;
			}
			else
			{
				break;
			}
		}
		
			

			

		




		UI UWU;
		UWU.Interface(Time, ProcessorsList, ProcessorCount, &BLK, &TRM);
		system("pause");
		system("cls");


	}
}
int Scheduler::getTime() {
	return Time;
}


int Scheduler::SigKill() {
	SIGKILL Signal;
	sigkill.peek(Signal);
	if (getTime() == Signal.Time) {
		sigkill.deQueue(Signal);
		return Signal.pID;
	}
	return 0;
}


void Scheduler::Simulate()
{
	Read();
	Time = 0;
	ProcessorCount = 0;
	ProcessorsList = new Processor * [NF + NR + NS];
	for (int i = 0; i < NF + NR + NS; i++) {
		ProcessorsList[i] = nullptr;
	}
	InitializeProcessors();


	Process* Prc;
	int ProcessorAddCounter = 0;
	int TempRandomNumber;

	while (TRM.getCount()!=M)//Temporary condition to test, this is the while for every timestep , the end condition would be in this while.
	{
		Time++;//Increments the time 

		/////////////////////////////////////////////////////////////////////////////////////////////////////
				//Adding the arrived Processes to the processors.
		while (true) {

			NEW.peek(Prc);
			if (Prc->getArrivalTime() == Time)//checks to see if the process is now in its arrival time;
			{
				AddtoRDY(Prc); //Add To the current process
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
		}
			///////////////////////////////////////////////////////////////////////////////////////////////////////\
			
 
			// Step iii of the simulate function
			for (int i = 0; i < ProcessorCount; i++)
			{
				ProcessorsList[i]->Simulate();
			}
			//////////////////////////////////////////////////////////////////////////////////////////////////////

			
			TempRandomNumber= rand() % 100 + 1; // generate a random number between 1 and 100
			if (TempRandomNumber < 10 && !BLK.isEmpty()) {
				BLK.deQueue(Prc);
 				ProcessorsList[ProcessorAddCounter]->AddToRDY(Prc);
				ProcessorAddCounter++;
				if (ProcessorAddCounter == ProcessorCount)
					ProcessorAddCounter = 0;
			}

			///////////////////////////////////////////////////////////////////////////////////////////////////////
			TempRandomNumber = rand() % M + 1;

			for (int i = NR + NS; i < ProcessorCount; i++)
			{
				ProcessorsList[i]->TerminateProcess(TempRandomNumber);
			}



		
		UI UWU;
		UWU.Interface(Time, ProcessorsList, ProcessorCount, &BLK, &TRM);
		system("pause");
		system("cls");
		

	}
















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
		P = new FCFS(this);
		ProcessorsList[ProcessorCount++] = P;
	}
}


// if mode = 0 it gets the index of the processor with shortest finish time
// if mode = 1 it gets the index of the SJF processor with shortest finish time
// if mode = 2 it gets the index of the RR processor with shortest finish time
int Scheduler::getShortestFinishTime(int mode)
{
	int min = 10000; //minumum cputime
	int c;//index which min is at
	
	for (int i = 0; i < ProcessorCount; i++)
	{
		if (mode == 1)
		{
			if (!(ProcessorsList[i]->getType() == "SJF")) //checks if it's a SJF processor
			{
				continue;
			}
		}
		else if (mode == 2)
		{
			if (!(ProcessorsList[i]->getType() == "RR")) //checks if it's a RR processor
			{
				continue;
			}
		}

		if (ProcessorsList[i]->getfinishtime() < min) {
			min = ProcessorsList[i]->getfinishtime(); //set min as the  count
			c = i;  //set index
		}
	}
	return c;
}
int Scheduler::getLongestFinishTime() {
	int max = 0; //minumum cputime
	int c;//index which min is at
	for (int i = 0; i < ProcessorCount; i++) {
		if (ProcessorsList[i]->getfinishtime() > max) {
			max = ProcessorsList[i]->getfinishtime(); //set max as the  count
			c = i;  //set index
		}
	}
	return c;
}

void Scheduler::AddtoRDY(Process* P) {
	int c = getShortestFinishTime();
	ProcessorsList[c]->AddToRDY(P);
	ProcessorsList[c]->addfinishtime(P);
}

void Scheduler::Migrate(Process* P, int mode)
{
	int c = getShortestFinishTime(mode);
	ProcessorsList[c]->AddToRDY(P);
	ProcessorsList[c]->addfinishtime(P);
}

void Scheduler::AddtoTRM(Process* P)
{
	TRM.enQueue(P);
	P->setState("TRM");
 
}

void Scheduler::AddtoBLK(Process* P)
{
	BLK.enQueue(P);
	P->setState("BLK");
}

void Scheduler::AddtoORPH(Process* P)
{
	ORPH.enQueue(P);
	P->setState("ORPH");
}

void Scheduler::CheckBLK()
{
	Process* prc;
	BLK.peek(prc);

	if (BLK.isEmpty())
	{
		return;
	}

	
	if (prc->checkIORequestDurationTime())
	{
		//AddToShortestRDYqueue//**************************************
	}
	
	




}

void Scheduler::WorkSteal()
{
	int shortestIndex = getShortestFinishTime();
	int longestIndex = getLongestFinishTime();
	
	int StealLimit = (ProcessorsList[longestIndex]->getfinishtime() - ProcessorsList[shortestIndex]->getfinishtime()) / ProcessorsList[longestIndex]->getfinishtime();

	while (StealLimit > 0.4)
	{
		
		AddtoRDY(ProcessorsList[longestIndex]->StealProcess());
		StealLimit = (ProcessorsList[longestIndex]->getfinishtime() - ProcessorsList[shortestIndex]->getfinishtime()) / ProcessorsList[longestIndex]->getfinishtime();
	}
	
	


}

Scheduler::~Scheduler()
{
	for (int i = 0; i < ProcessorCount; i++) {
		delete ProcessorsList[i];
	}
	delete[] ProcessorsList;
}


