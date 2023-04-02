#pragma once
#include "Scheduler.h"
#include "Processor.h"
#include"Queue.h"
class RR :
    public Processor
{
    int RunningTimeSlice = pScheduler->TimeSliceOfRR();
    Queue<Process*> RDY;
    Scheduler* pScheduler;
public:
    virtual void ScheduleAlgo();
    virtual void AddToRDY(Process* Prc);
    RR(Scheduler*);

};

