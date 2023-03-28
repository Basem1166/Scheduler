#include<fstream>
#include<iostream>

#include"Scheduler.h"

using namespace std;

int main()
{
	Scheduler Schedule;

	Schedule.Read();
	Schedule.InitializeProcessors();



	system("pause");
	return 0;
}