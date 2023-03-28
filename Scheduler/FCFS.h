#pragma once
#include "Processor.h"
class FCFS :
    public Processor
{
private:
    Queue<Process*> RDY;
public:
    virtual void ScheduleAlgo();
};

