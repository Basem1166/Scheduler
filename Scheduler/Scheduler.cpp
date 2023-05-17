#include "Scheduler.h"

Scheduler::Scheduler()
{
	Read(); //Read input file 
	OriginalProcessesCount = M; //Number of processes before foking
	Time = 0;
	ProcessorCount = 0;
	ProcessorsList = new Processor * [NF + NR + NS+ NE]; // declare processor list 
	for (int i = 0; i < NF + NR + NS + NE; i++) {
		ProcessorsList[i] = nullptr;
	}
	InitializeProcessors(); // create the specified processors from input file 
	srand(time(NULL)); // seed the random number generator with the current time
	BeforeDLCount = 0; // counter of processes that will finish before their Deadline
	StolenProcesses = 0; // Counter of Stolen processes

}

void Scheduler::Read()
{
	// Variables to be used when creating new processes
	int AT;
	int pID;
	int CT;
	int Deadline;
	int N;
	int IO_R;
	int IO_D;
	char temp = ' '; // character used to temporarily store the brackets and commas+

	int RTF, MaxW, ForkProbability, TimeSliceOfRR,OverHeatTime;
	

	ifstream fin("Input.txt", ios::in); //Creates an fstream object and opens the input file

	if (!fin.is_open()) //checks if the file didn't open properly
	{
		cout << "Error openning the file please check the file location";

	}
	else
	{
		fin >> NF >> NS >> NR >> NE >> TimeSliceOfRR >> RTF >> MaxW >> STL >> ForkProbability >>OverHeatTime>> M; // Inputs the necessary data from the input file to the variables

		RR::setRTF(RTF);
		RR::setTimeSlice(TimeSliceOfRR);
		FCFS::setMaxW(MaxW);
		FCFS::setForkProb(ForkProbability); //Sets Static members necessary
		Processor::setOverHeatTime(OverHeatTime);

		for (int i = 0; i < M; i++)
		{
			fin >> AT >> pID >> CT>> Deadline >> N;

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
			Process* temp = new Process(AT, pID, CT, Deadline, N, ior); //creates a new process after reading each line
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
	if (ProcessorCount==0) // if no processors 
	{
		return;
	}
	Process* Prc;
	int TempRandomNumber;
	UI UWU; //Creates UI Object
	

	int mode = UWU.Mode();
	system("cls");
	bool first = true;

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

		for (int i = 0; i < ProcessorCount; i++) // Schedule Algo for all processors 
		{
			ProcessorsList[i]->ScheduleAlgo(Time);
		}

		CheckBLK(); //Check the BLK list to handle IOs 

		if (Time%STL==0) //Check to see if its a multiple of STL
		{
			WorkSteal(); // call the WorkSteal Function 
		}
		

		if (mode == 3 && first) 
		{
			UWU.Interface(Time, ProcessorsList, ProcessorCount, &BLK, &TRM, mode);
			first = false;
		}
		else if(mode != 3)
		{
			UWU.Interface(Time, ProcessorsList, ProcessorCount, &BLK, &TRM, mode);
			system("cls");
		}
		
	
			

		




		


	}
	OutPut(); // call the output function 
}   



int Scheduler::SigKill() {
	SIGKILL Signal; //creates a struct for sigkill
	sigkill.peek(Signal); //checks the first signal in the queue
	if (Time == Signal.Time) // if time matches the signal wanted to be killed proceed to remove it from queue and returns its id to be killed
	{
		sigkill.deQueue(Signal);
		return Signal.pID;
	}
	return -2; // else returns an impossible process ID
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
	for (int i = 0; i < NR; i++) // Initialize all processors using the numbers from the input file 
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
	for (int i = 0; i < NE; i++)
	{
		P = new EDF(this);
		ProcessorsList[ProcessorCount++] = P;
	}
}


// if mode = 0 it gets the index of the processor with shortest finish time
// if mode = 1 it gets the index of the SJF processor with shortest finish time
// if mode = 2 it gets the index of the RR processor with shortest finish time
// if mode = 3 it gets the index of the FCFS processor with shortest finish time
int Scheduler::getShortestFinishTime(int mode)
{
	
	int min = INT_MAX; //minumum cputime
	int c = -1;//index which min is at
	for (int i = 0; i < ProcessorCount; i++)
	{
		if (ProcessorsList[i]->getState()=="STOP") // if overheated continue 
		{
			continue;
		}

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
		else if (mode == 3)
		{
			if (!(ProcessorsList[i]->getType() == "FCFS")) //checks if it's a FCFS processor
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
	int max = -1; //minumum cputime
	int c ;//index which min is at
	for (int i = 0; i < ProcessorCount; i++) {
		if (ProcessorsList[i]->getState() == "STOP")//if overheated continue
		{
			continue;
		}
		if (ProcessorsList[i]->getfinishtime() > max) {
			max = ProcessorsList[i]->getfinishtime(); //set max as the  count
			c = i;  //set index
		}
	}
	return c;
}

void Scheduler::AddtoRDY(Process* P, int mode) {
	int c = getShortestFinishTime(mode); // gets index of shortest processor
	if (c == -1) {
		AddtoTRM(P); // if no processor to add to -> processor is overheated -> add to TRM 
		return;
	}
	ProcessorsList[c]->AddToRDY(P); // add to rdy of shortest expectedfinishtime
	
	
}
void Scheduler::Fork(Process* P) {
	if (!P->isparent()) {
		M++;
		Process* temp = new Process(Time, M, P->getTimeCounter(), P->getDeadline(), 0, NULL);
		P->setchild(temp);
		AddtoRDY(temp, 3);
	}
	
}

bool Scheduler::Migrate(Process* P, int mode)
{
	int count = 0;
	if (mode==1 && NS==0) //checks if mode = 1 and there is no SJF processors so it returns false since there will be no migration.
	{
		return false;
	}
	if (mode==2 && NR==0) //checks if mode = 2 and there is no RR processors so it returns false since there will be no migration.
	{
		return false;
	}
	if (mode==1) //if there are available SJF processors
	{
		for (int i = 0; i < ProcessorCount; i++)
		{
			if (ProcessorsList[i]->getState() == "STOP" && ProcessorsList[i]->getType() == "SJF") //checks if the processor is overheated or not
			{
				count++;
			}
		}
		if (count == NS) //Returns false and doesn't migrate if it is
		{
			return false;
		}
	}
	if (mode == 2)
	{
		for (int i = 0; i < ProcessorCount; i++)
		{
			if (ProcessorsList[i]->getState() == "STOP" && ProcessorsList[i]->getType() == "RR") //checks if the processor is overheated or not
			{
				count++;
			}
		}
		if (count == NR) //Returns false and doesn't migrate if it is
		{
			return false;
		}
	}
	
	AddtoRDY(P, mode); //Adds it to the shortes ready of the wanted processor type
	return true; //return true migration was successful
}
//mode=0 -> normal process
//mode=1 -> orphan process
void Scheduler::AddtoTRM(Process* P, int mode)
{
	if (Time < P->getDeadline()) 
	{
		BeforeDLCount++; // if terminate time less than expected finish time add the stastic
	}
	TRM.enQueue(P); // add to TRM queue
	if (mode)
	{
		P->setState("ORPH"); // set state to orphan
	}
	else
	{
		P->setState("TRM"); // set state to TRM
	}
	CheckOrphan(P); // checks if the process had any children 
	P->setTerminationT(Time); // sets the termination time of the process 

}

void Scheduler::AddtoBLK(Process* P)
{
	BLK.enQueue(P); // enqueue the BLK 
	P->setState("BLK"); // sets state to BLK
}



void Scheduler::CheckBLK()
{
	Process* prc;
	BLK.peek(prc); // peeks the front of BLK

	if (BLK.isEmpty())
	{
		return; // checks if BLK is empty 
	}

	
	if (prc->checkIORequestDurationTime()) // returns 1 if IODuration passed , 0 otherwise 
	{
		BLK.deQueue(prc); //Remove from BLK	
		AddtoRDY(prc);   // Add to Shortest RDY
	}
	
	




}
void Scheduler::CheckOrphan(Process* prc) // checks to see if the process is a parent so that it terminates children
{
	int Pid;
	if (prc->isparent()) //checks if parent 
	{
		Pid=prc->getChildID(); // gets the ID of Child 
		for (int i = NR + NS; i < ProcessorCount; i++)
		{
			ProcessorsList[i]->TerminateProcess(Pid,1); //Kills the child if found 
		}
	}
	


}
void Scheduler::WorkSteal()
{
	
	int shortestIndex = getShortestFinishTime(); //get index of shortest Processor
	if (shortestIndex == -1)
		return;       // if =-1 means all are  overheated and does no workstealing 
	int longestIndex = getLongestFinishTime();	 // get index of longest Processor
	
	if (ProcessorsList[longestIndex]->getfinishtime() == 0) // if longest has no processes, does no work stealing 
		return;
		// calculate steal limit
		float StealLimit = (float)(ProcessorsList[longestIndex]->getfinishtime() - ProcessorsList[shortestIndex]->getfinishtime()) / ProcessorsList[longestIndex]->getfinishtime();
		
 		while (StealLimit > 0.4)
		{
			Process* prc = ProcessorsList[longestIndex]->StealProcess(); //tell the longest Processor to dequeue a process and returns it 
			if (prc)
			{
				ProcessorsList[shortestIndex]->AddToRDY(prc); //adds to shortest RDY 
				StolenProcesses++; //adds to statistics
			}
			else
			{
				break; // if no process found in RDY
			}

			
			if (ProcessorsList[longestIndex]->getfinishtime() == 0) // if longest has no more processes 
				return;
   			StealLimit = (float)(ProcessorsList[longestIndex]->getfinishtime() - ProcessorsList[shortestIndex]->getfinishtime()) / ProcessorsList[longestIndex]->getfinishtime();
			//recalculates the steal limit 
		}
	
	


}




void Scheduler::OutPut()
{
	ofstream fout("Output.txt", ios::out); //Creates an fstream object and opens the output file
	Process* temp;
	UI UWU; //Creates UI Object
	int idk = 0;
	if (fout.is_open())
	{
		int TotalWT = 0, TotalRT = 0, TotalTRT = 0, TotalBusyTime = getTotalBusyTime();

		float RTFPercenage = (static_cast<float>(RR::getMigrationNumber()) / M) * 100; // Calculates RTF Percenage
		float MaxWPercentage = (static_cast<float>(FCFS::getMigrationNumber()) / M) * 100; // Calculates MaxW Percentage
		float StolenPercentage = (static_cast<float>(StolenProcesses) / M) * 100; // Calculates Stolen Percentage

		float ForkedProcesses = M - OriginalProcessesCount; // Calculates Forked Processes
		float ForkedPercentage = (ForkedProcesses / M) * 100; // Calculates Forked Percentage

		float KilledPercentage = (static_cast<float>(FCFS::getKilledProcessesNumber()) / M) * 100; // Calculates Killed Percentage

		float BeforeDeadlinePercentage = (static_cast<float>(BeforeDLCount) / M) * 100; // Calculates Killed Percentage


		fout << "TT\tPID\tCT\tDL\tIO_D\t\tWT\tRT\tTRT"<<endl;

		while (TRM.deQueue(temp))
		{
			temp->setTRT();
			temp->setWT();
			TotalTRT += (temp->getTerminationTime() - temp->getArrivalTime()); //termination time
			TotalWT += temp->getWT();
			TotalRT += temp->getRT();
			fout << temp->getTerminationTime() << "\t" << temp->getProcessID() << "\t" << temp->getCPUTime() << "\t" << temp->getDeadline() << "\t" << temp->getIO_D();
			fout   << "\t\t" << temp->getWT() << "\t" << temp->getRT() << "\t" << temp->getTerminationTime()- temp->getArrivalTime() << endl;
			delete temp;
		}

		fout << endl << "Processes: " << M << endl;
		fout << "Avg WT = " << TotalWT / M << ",\t" << "Avg RT = " << TotalRT / M << ",\t" << "Avg TRT = " << TotalTRT / M << endl;
		fout << "Migration %:\t RTF = " << RTFPercenage << "%, \t MaxW = " << MaxWPercentage << "%" << endl;
		fout << "Work Steal %: " << StolenPercentage << "%" << endl;
		fout << "Forked Process %: " << ForkedPercentage << "%" << endl;
		fout << "Killed Process %: " << KilledPercentage << "%" << endl;

		fout << "Before Expected Deadline%: " << BeforeDeadlinePercentage << "%" << endl << endl;

		fout << "Processors: " << NF + NR + NS + NE << " [ " << NR << " RR, " << NS << " SJF, " << NF << " FCFS, " << NE << " EDF ]" << endl;

		fout << "Processors Load" << endl;
		for (int i = 0; i < NF + NR + NS + NE; i++)
		{
			float LoadPercentage = (static_cast<float>(ProcessorsList[i]->getBusyTime()) / TotalBusyTime) * 100;
			if (i == NF + NR + NS + NE - 1)
			{
				fout << "P" << i + 1 << " = " << LoadPercentage << "%\n";
			}
			else
			{
				fout << "P" << i + 1 << " = " << LoadPercentage << "%,\t";
			}
			
		}

		fout <<endl<< "Processors Utiliz" << endl;
		float TotalUtil = 0;
		for (int i = 0; i < NF + NR + NS + NE; i++)
		{

			float UtilPercentage = (static_cast<float>(ProcessorsList[i]->getBusyTime()) / (ProcessorsList[i]->getBusyTime()+ ProcessorsList[i]->getIdleTime())) * 100;
			TotalUtil += UtilPercentage;
			if (i == NF + NR + NS + NE - 1)
			{
				fout << "P" << i + 1 << " = " << UtilPercentage << "%\n";
			}
			else
			{
				fout << "P" << i + 1 << " = " << UtilPercentage << "%,\t";
			}

		}
		float AvgUtil = TotalUtil / (NF + NR + NS + NE);
		fout << "Avg utilization = " << AvgUtil << "%";

	}
	UWU.OutputFinished();
}

int Scheduler::getTotalBusyTime()
{
	int Total = 0;
	for (int i = 0; i < NF + NR + NS + NE; i++)
	{
		Total += ProcessorsList[i]->getBusyTime();
	}
	return Total;
}



Scheduler::~Scheduler()
{ 
	//deletes all dynamically allocated memory
	for (int i = 0; i < ProcessorCount; i++) {
		delete ProcessorsList[i];
	}
	delete[] ProcessorsList;


}


