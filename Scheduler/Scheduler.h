#pragma once
#include<fstream>
#include<iostream>

#include"Queue.h"
#include"pQueue.h"

#include"Process.h"

using namespace std;
class Scheduler
{
private:
	Queue<Process*> NEW;
public:


	void Read(int& NF, int& NS, int& NR, int& RR, int& RTF, int& MaxW, int& M);
};

