#pragma once
#include "Processor.h"
#include "Queue.h"
class FCFS :
    public Processor
{
private:
    Queue<Process*> RDY;
public:
    virtual Process* ScheduleAlgo();
    virtual void AddToRDY(Process* Prc);
};

