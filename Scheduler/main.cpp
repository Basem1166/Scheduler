#include<fstream>
#include<iostream>

#include"Scheduler.h"

using namespace std;

int main()
{
	Scheduler Schedule;

	Schedule.InitializeProcessors();
	Schedule.Execute();


	system("pause");
	return 0;
}