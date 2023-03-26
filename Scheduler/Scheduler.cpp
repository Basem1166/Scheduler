#include "Scheduler.h"

void Scheduler::Read(int& NF, int& NS, int& NR, int& RR, int& RTF, int& MaxW, int& M)
{

	ifstream fin("Input.txt", ios::in); //Creates an fstream object and opens the input file\

	if (!fin.is_open()) //checks if the file didn't open properly
	{
		cout << "Error openning the file please check the file location";

	}
	else
	{
		fin >> NF >> NS >> NR >> RR >> RTF >> MaxW >> M; // Inputs the necessary data from the input file to the variables
	}
	cout << NF << " " << NS << " " << NR << " " << RR << " " << RTF << " " << MaxW << " " << M << " ";

}
