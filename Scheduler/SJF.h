#pragma once
#include "Processor.h"
#include "Process.h"
#include "pQueue.h"
#include "Scheduler.h"
class SJF :
    public Processor
{
private:
    pQueue <Process*> RDY;
    int in = 0;
    Scheduler* pScheduler;
public:
    void ScheduleAlgo();
    virtual void AddToRDY(Process* Prc);
    virtual void Simulate();
    virtual void TerminateProcess(int);
    void PrintRDY();
    int getRDYCount();
    virtual void addfinishtime(Process* Prc); //function to add the cpu time
    virtual int getfinishtime();
    SJF(Scheduler* scheduler);
   
};

