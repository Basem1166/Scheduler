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
    Process* ScheduleAlgo();
    virtual void AddToRDY(Process* Prc);
    SJF(Scheduler* scheduler);
   
};

