#include "DrawBoard.h"
#include <iostream>

void Draw::drawBoard(std::vector<Cell*> _board)
{
	char out;
	int counter = 0;
	int lineCount = 0;


	std::cout << std::endl << "  0 1 2 3 4 5 6 7 8 9" << std::endl << "0"; 


	for (auto it = _board.begin(); it != _board.end(); it++)
	{
		if (counter == 10)
		{
			lineCount++;
			counter = 0;
			std::cout << std::endl << lineCount;

		}


		switch ((*it)->getType())
		{
		case 0:
			out = '~';
			break;
		case 1:
			out = '#';
			break;
		case 2:
			out = 'H';
			break;
		case 3:
			out = 'X';
			break;
		}
		std::cout << " "  << out;

		counter++;


	}
	std::cout << std::endl;
}

void Draw::drawDebugBoard(std::vector<Cell*> _board)
{
	char out;
	int counter = 0;
	int lineCount = 0;


	std::cout << std::endl << "  0 1 2 3 4 5 6 7 8 9" << std::endl << "0";


	for (auto it = _board.begin(); it != _board.end(); it++)
	{
		if (counter == 10)
		{
			lineCount++;
			counter = 0;
			std::cout << std::endl << lineCount;

		}
		std::cout << (*it)->getShotChance() << " ";



	}
	std::cout << std::endl;
}


/*
0 - Empty
1 - Ship
2 - Miss
3 - Hit
*/