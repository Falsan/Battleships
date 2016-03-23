#include "Board.h"

board::board(gameData * _GD)
{
	m_GD = _GD;
	createBoard();
}

board::~board()
{
	for (int i = 0; i < m_GD->GetBoardDi(); i++)
	{
		for (int j = 0; j < m_GD->GetBoardDi(); j++)
		{
			delete m_board[i][j];
		}
	}
}

void board::createBoard()
{
	for (int i = 0; i < m_GD->GetBoardDi(); i++)
	{
		for (int j = 0; j < m_GD->GetBoardDi(); j++)
		{
			m_board[i][j] = new Cell;
		}
	}
}