#include "SJF.h"

void SJF::ScheduleAlgo()
{
}

void SJF::AddToRDY(Process* Prc)
{
	RDY.enQueue(Prc, Prc->getCPUTime());
}
