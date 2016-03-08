#include "Board.h"

board::board()
{
	createBoard();
}

board::~board()
{
	for (int i = 0; i < m_boardDimentions; i++)
	{
		for (int j = 0; j < m_boardDimentions; j++)
		{
			delete m_board[i];
		}
	}
	m_board.clear();
}

void board::createBoard()
{
	for (int i = 0; i < m_boardDimentions; i++)
	{
		for (int j = 0; j < m_boardDimentions; j++)
		{
			m_board.push_back(new Cell);
		}
	}
}