#pragma once
#include "Scheduler.h"
#include "Processor.h"
#include"Queue.h"
class RR :
    public Processor
{
    static int TimeSlice;
    static int MigrationNumber; // changes only from new->rdy
    static int NumberOfProcesses;
    static int RTF; //makes more sense to make this a static data member too


    int RunningTimeSlice; //to decrement it until zero so i can dequeue and requeue it into RDY
    Queue<Process*> RDY;
    Scheduler* pScheduler;
public:
    virtual void ScheduleAlgo();
    virtual void Simulate();
    virtual void AddToRDY(Process* Prc);
    virtual void TerminateRandomProcess();

    static void setRTF(int RTF_);
    static void setTimeSlice(int TimeSlice_);

    void PrintRDY();
    int getRDYCount();

    RR(Scheduler*);

};
