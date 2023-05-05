#pragma once
#include "Scheduler.h"
#include "Processor.h"
#include "List.h"
class FCFS :
    public Processor
{
private:
    static int NumberOfProcesses;
    static int NumberOfMaxW;
    static int ForkedProcesses;
    static int KilledProcesses;

    static int MaxW; 
    static int ForkProbability;//makes more sense to make them a static data member too

    LinkedList<Process*> RDY;
    Scheduler* pScheduler;
      
public:
    FCFS(Scheduler* pSch);
    virtual void ScheduleAlgo();
    virtual void Simulate();
    virtual void AddToRDY(Process* Prc);
    virtual void TerminateProcess(int);

    void PrintRDY();
    int getRDYCount();
    int getReadyWaitTime(); //Used in the migration from FCFS to RR
    virtual void addfinishtime(Process* Prc); //function to add the cpu time
    virtual int getfinishtime();

    static void setMaxW(int maxW);
    static void setForkProb(int Prob);
};

