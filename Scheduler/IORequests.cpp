#include "IORequests.h"


IORequests::IORequests(int RT, int DT)
{
	RequestTime = RT;
	Duration = DT;
}

int IORequests::getRequestTime()
{
	return RequestTime;
}

int IORequests::getDuration()
{
	return Duration;
}




