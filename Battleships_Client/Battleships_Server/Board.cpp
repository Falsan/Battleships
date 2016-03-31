#include "Board.h"

Board::Board(gameData * _GD)
{
	m_GD = _GD;
	createBoard();
}

Board::~Board()
{
	for (int i = 0; i < m_GD->GetBoardDi(); i++)
	{
		for (int j = 0; j < m_GD->GetBoardDi(); j++)
		{
			delete m_board[i][j];
		}
	}
}

void Board::createBoard()
{
	for (int i = 0; i < m_GD->GetBoardDi(); i++)
	{
		for (int j = 0; j < m_GD->GetBoardDi(); j++)
		{
			m_board[i][j] = new Cell;
		}
	}
}