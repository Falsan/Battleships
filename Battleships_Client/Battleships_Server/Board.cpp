#include "Board.h"

Board::Board()
{
	createBoard();
}

Board::~Board()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j <10; j++)
		{
			delete m_board[i][j];
		}
	}
}

void Board::createBoard()
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			m_board[i][j] = new Cell;
		}
	}
}