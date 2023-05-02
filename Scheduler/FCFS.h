#pragma once
#include "Scheduler.h"
#include "Processor.h"
#include "List.h"
#include "SIGKILL.h"
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

    static Queue<SIGKILL> SigKill;

    LinkedList<Process*> RDY;
    Scheduler* pScheduler;
      
public:
    FCFS(Scheduler* pSch);
    virtual void ScheduleAlgo();
    virtual void Simulate();
    virtual void AddToRDY(Process* Prc);
    virtual void TerminateRandomProcess(int);

    void PrintRDY();
    int getRDYCount();

    static void setMaxW(int maxW);
    static void setForkProb(int Prob);
    static void AddSigKill(SIGKILL s);
};

