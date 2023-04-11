#pragma once
#include "Scheduler.h"
#include "Processor.h"
#include"Queue.h"
class RR :
    public Processor
{
    static int MigrationNumber; // changes only from new->rdy
    static int NumberOfProcesses;
    int RunningTimeSlice; //to decrement it until zero so i can dequeue and requeue it into RDY
    int RTF;
    int TimeSlice;
    Queue<Process*> RDY;
    Scheduler* pScheduler;
public:
    virtual void ScheduleAlgo();
    virtual void Simulate();
    virtual void AddToRDY(Process* Prc);
    virtual void TerminateRandomProcess();
    RR(Scheduler*);

};

