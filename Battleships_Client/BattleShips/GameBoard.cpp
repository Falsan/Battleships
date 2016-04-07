#include "Board.h"

Board::Board()
{
	for (auto it = board.begin(); it != board.end(); it++)
	{
		(*it) = new Cell;
	}
}

Board::~Board()
{
	for (auto it = board.begin(); it != board.end(); it++)
	{
		delete *it;
	}
}

Cell* Board::getCell(int x, int y)
{
	int index = 1;

	return board[(index * x) + y]; //sets the vector to essentially have two dimensions
}

void Board::setCell(int type, int x, int y)
{
	getCell(x, y)->setType(type);
}

void Board::makeShip(int size, int orientation, std::pair<int, int> origin)
{
	ships.push_back(new Ship(size, orientation, origin));
}