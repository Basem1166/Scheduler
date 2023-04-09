#pragma once
#include "Scheduler.h"
#include "Processor.h"
#include "List.h"
class FCFS :
    public Processor
{
private:
    LinkedList<Process*> RDY;
    Scheduler* pScheduler;
public:
    FCFS(Scheduler* pSch);
    virtual void ScheduleAlgo();
    virtual void Simulate();
    virtual void AddToRDY(Process* Prc);
    virtual void TerminateRandomProcess();
};

