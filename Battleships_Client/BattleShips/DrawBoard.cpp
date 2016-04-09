#include "DrawBoard.h"
#include <iostream>

void Draw::drawBoard(std::vector<Cell*> _board)
{
	char out;
	int counter = 0;
	for (auto it = _board.begin(); it != _board.end(); it++)
	{
		switch ((*it)->getType())
		{
		case 0:
			out = 'E';
			break;
		case 1:
			out = 'S';
			break;
		case 3:
			out = 'M';
			break;
		case 4:
			out = 'H';
			break;
		}
		std::cout << out;

		counter++;
		if (counter == 9)
		{
			counter = 0;
			std::cout << std::endl;
		}

	}
}

/*
0 - Empty
1 - Ship
2 - Miss
3 - Hit
*/