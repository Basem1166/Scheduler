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
    LinkedList<Process*> RDY;
    Scheduler* pScheduler;
    bool isChild;
    bool isParent;
    Process* Child;
    int ForkProbability;
    int MaxW;   
public:
    FCFS(Scheduler* pSch);
    virtual void ScheduleAlgo();
    virtual void Simulate();
    virtual void AddToRDY(Process* Prc);
    virtual void TerminateRandomProcess();
};

