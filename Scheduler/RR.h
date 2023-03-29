#pragma once
#include "Processor.h"
#include"Queue.h"
class RR :
    public Processor
{
    Queue<Process*> RDY;
public:
    virtual void ScheduleAlgo();
    virtual void AddToRDY(Process* Prc);

};

