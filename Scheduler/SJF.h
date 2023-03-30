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
   
public:
    void ScheduleAlgo();
    virtual void AddToRDY(Process* Prc);
    
   
};

