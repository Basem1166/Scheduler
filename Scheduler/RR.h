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
    virtual void ScheduleAlgo(int);
    virtual void Simulate();
    virtual void AddToRDY(Process* Prc);
    virtual void TerminateProcess(int,int);
    virtual Process* StealProcess();
    virtual void EmptyProcessor();
    static void setRTF(int RTF_);
    static void setTimeSlice(int TimeSlice_);
    static void IncrementMigrationNumber();
    static int getMigrationNumber();
    virtual string getState();

    void PrintRDY();
    string getType();
    int getRDYCount();
    virtual void addfinishtime(Process* Prc); //function to add the cpu time
    virtual int getfinishtime();

    RR(Scheduler*);

};
