#include "DrawBoard.h"
#include <iostream>

void draw::drawBoard(std::vector<Cell*> _board)
{
	char out;
	for (auto it = _board.begin(); it != _board.end(); it++)
	{
		switch ((*it)->getType())
		{
		case 0:
			out = ' ';
			break;
		case 1:
			out = 'X';
			break;
		case 3:
			out = '$';
			break;
		case 4:
			out = '@';
			break;
		}
		std::cout << out;

	}
}