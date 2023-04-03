#pragma once
#include "Scheduler.h"
#include "Processor.h"
#include"Queue.h"
class RR :
    public Processor
{
    int RunningTimeSlice; //to decrement it until zero so i can dequeue and requeue it into RDY
    Queue<Process*> RDY;
    Scheduler* pScheduler;
public:
    virtual void ScheduleAlgo();
    virtual void AddToRDY(Process* Prc);
    RR(Scheduler*);

};

