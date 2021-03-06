#include "Board.h"

Board::Board()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_board.push_back(new Cell);
		}
	}
}

Board::~Board()
{
	for (auto it = m_board.begin(); it != m_board.end(); it++)
	{
		delete *it;
	}
}

Cell* Board::getCell(int x, int y)
{
	int index = 10;

	return m_board[(index * x) + y]; //sets the vector to essentially have two dimensions
}

Cell* Board::getCell(int loc)
{
	return m_board[loc];
}


void Board::setCell(int type, int x, int y)
{
	getCell(x, y)->setType(type);
}
void Board::setCell(int loc, int _in)
{
	m_board[loc]->setType(_in);
}

