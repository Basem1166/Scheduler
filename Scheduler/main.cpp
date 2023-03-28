#include<fstream>
#include<iostream>

#include"Scheduler.h"

using namespace std;

int main()
{
	Scheduler Schedule;

	Schedule.Read();
	Schedule.Initialize();



	system("pause");
	return 0;
}