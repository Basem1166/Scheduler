#pragma once
#include "Processor.h"
#include "Process.h"
#include "pQueue.h"
#include "Scheduler.h"
class EDF :
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
    virtual void TerminateProcess(int, int);
    virtual string getState();
    virtual void EmptyProcessor();
    virtual Process* StealProcess();
    void PrintRDY();
    int getRDYCount();
    string getType();
    virtual void addfinishtime(Process* Prc); //function to add the cpu time
    virtual int getfinishtime();
    EDF(Scheduler* scheduler);

};

