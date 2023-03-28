#pragma once
#include "Processor.h"
#include "Process.h"
#include "pQueue.h"
class SJF :
    public Processor
{
private:
    Queue<Process*> RDY;
   
public:
    void ScheduleAlgo();
    
   
};

