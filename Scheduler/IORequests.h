#pragma once
class IORequests
{
private:
	int RequestTime;
	int Duration;

public:
	IORequests(int RT = 0, int DT = 0);

	int getRequestTime();
	int getDuration();

};

