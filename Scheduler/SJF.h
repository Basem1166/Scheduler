#pragma once
#include "Processor.h"
#include"pQueue.h"
#include "Process.h"
class SJF :
    public Processor
{
private:
    
    pQueue<Process*> RDY;
public:
    void ScheduleAlgo();
    
   
};

