#include "OutPut.h"

void output::printBoard(std::vector<Cell*> _inVec)
{
	std::cout << "0\t 1\t 2\t 3\t 4\t 5\t 6\t 7\t 8\t 9\t" << std::endl;
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j <10; j++)
		{
			int HOLD = i + j;
			printElement(HOLD);
		}
		std::cout << std::endl;
	}
	
}


void output::printElement(int _inPos)
{
	switch (_inPos)
	{
	case 0: 
		//Empty space
		PrintOut(".");
		break;
	case 1:
		//bit of a boat
		PrintOut("O");
		break;
	case 2:
		//Shot/ missed shot
		PrintOut("X");
		break;
	case 3:
		//Hit Shot
		PrintOut("#");
		break;
	}
	std::cout << "\t";
}
/*
0 - empity
1 - Boat
2 - shot
3 - shot + boat
*/



template <class T>
void output::PrintOut(T& _in)
{
	std::cout << _in;
}

template <class T>
void output::PrintOutNL(T&)
{
	std::cout << T << std::endl;
}