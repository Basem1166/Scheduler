#pragma once
#include "Processor.h"
#include "Process.h"
#include "Queue.h"
class SJF :
    public Processor
{
private:
    Queue<Process*> RDY;
   
public:
    void ScheduleAlgo();
    virtual void AddToRDY(Process* Prc);
    
   
};

