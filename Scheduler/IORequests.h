#pragma once
struct IORequests
{

	int RequestTime;
	int Duration;
	int FinishedTime;// time it enters BLK + Duration 

	IORequests(int RT = 0, int DT = 0);

	int getRequestTime();
	int getDuration();
	
};

