#pragma once
#include "Processor.h"
#include "Process.h"
#include "pQueue.h"
#include "Scheduler.h"
class SJF :
    public Processor,Scheduler
{
private:
    pQueue <Process*> RDY;
    int in = 0;
public:
    void ScheduleAlgo();
    virtual void AddToRDY(Process* Prc);
   
};

