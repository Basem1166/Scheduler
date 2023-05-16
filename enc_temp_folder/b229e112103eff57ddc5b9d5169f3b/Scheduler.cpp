#include "Scheduler.h"

Scheduler::Scheduler()
{
	Read();
	OriginalProcessesCount = M;
	Time = 0;
	ProcessorCount = 0;
	ProcessorsList = new Processor * [NF + NR + NS+ NE];
	for (int i = 0; i < NF + NR + NS + NE; i++) {
		ProcessorsList[i] = nullptr;
	}
	InitializeProcessors();
	srand(time(NULL)); // seed the random number generator with the current time
	BeforeDLCount = 0;
	StolenProcesses = 0;

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
	if (ProcessorCount==0)
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

		for (int i = 0; i < ProcessorCount; i++)
		{
			ProcessorsList[i]->ScheduleAlgo(Time);
		}

		CheckBLK();

		if (Time%STL==0)
		{
			WorkSteal();
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
	OutPut();
}   



int Scheduler::SigKill() {
	SIGKILL Signal;
	sigkill.peek(Signal);
	if (Time == Signal.Time) {
		sigkill.deQueue(Signal);
		return Signal.pID;
	}
	return -2;
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
	int c;//index which min is at
	for (int i = 0; i < ProcessorCount; i++) {
		if (ProcessorsList[i]->getState() == "STOP")
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

	int c = getShortestFinishTime(mode);
		ProcessorsList[c]->AddToRDY(P);
	
	
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
	if (mode==1 && NS==0)
	{
		return false;
	}
	if (mode==2 && NR==0)
	{
		return false;
	}
	if (mode==1)
	{
		for (int i = 0; i < ProcessorCount; i++)
		{
			if (ProcessorsList[i]->getState() == "STOP" && ProcessorsList[i]->getType() == "SJF")
			{
				count++;
			}
		}
		if (count == NS)
		{
			return false;
		}
	}
	if (mode == 2)
	{
		for (int i = 0; i < ProcessorCount; i++)
		{
			if (ProcessorsList[i]->getState() == "STOP" && ProcessorsList[i]->getType() == "RR")
			{
				count++;
			}
		}
		if (count == NR)
		{
			return false;
		}
	}
	
	AddtoRDY(P, mode);
	return true;
}
//mode=0 -> normal process
//mode=1 -> orphan process
void Scheduler::AddtoTRM(Process* P, int mode)
{
	if (Time < P->getDeadline())
	{
		BeforeDLCount++;
	}
	TRM.enQueue(P);
	if (mode)
	{
		P->setState("ORPH");
	}
	else
	{
		P->setState("TRM");
	}
	CheckOrphan(P);
	P->setTerminationT(Time);

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
		BLK.deQueue(prc);
		AddtoRDY(prc);
	}
	
	




}
void Scheduler::CheckOrphan(Process* prc) {
	int Pid;
	if (prc->isparent())
	{
		Pid=prc->getChildID();
		for (int i = NR + NS; i < ProcessorCount; i++)
		{
			ProcessorsList[i]->TerminateProcess(Pid,1);
		}
	}
	


}
void Scheduler::WorkSteal()
{
	int shortestIndex = getShortestFinishTime();
	int longestIndex = getLongestFinishTime();	
	
	if (ProcessorsList[longestIndex]->getfinishtime() == 0)
		return;
		
		float StealLimit = (float)(ProcessorsList[longestIndex]->getfinishtime() - ProcessorsList[shortestIndex]->getfinishtime()) / ProcessorsList[longestIndex]->getfinishtime();
		
 		while (StealLimit > 0.4)
		{
			Process* prc = ProcessorsList[longestIndex]->StealProcess();
			if (prc)
			{
				ProcessorsList[shortestIndex]->AddToRDY(prc);
				StolenProcesses++;
			}
			else
			{
				break;
			}

			
			if (ProcessorsList[longestIndex]->getfinishtime() == 0)
				return;
   			StealLimit = (float)(ProcessorsList[longestIndex]->getfinishtime() - ProcessorsList[shortestIndex]->getfinishtime()) / ProcessorsList[longestIndex]->getfinishtime();
			
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
		float RTFPercenage = (static_cast<float>(RR::getMigrationNumber()) / M) * 100;
		float MaxWPercentage = (static_cast<float>(FCFS::getMigrationNumber()) / M) * 100;
		float StolenPercentage = (static_cast<float>(StolenProcesses) / M) * 100;

		float ForkedProcesses = M - OriginalProcessesCount;
		float ForkedPercentage = (ForkedProcesses / M) * 100;

		float KilledPercentage = (static_cast<float>(FCFS::getKilledProcessesNumber()) / M) * 100;

		float BeforeDeadlinePercentage = (static_cast<float>(BeforeDLCount) / M) * 100;


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
	for (int i = 0; i < ProcessorCount; i++) {
		delete ProcessorsList[i];
	}
	delete[] ProcessorsList;
}


