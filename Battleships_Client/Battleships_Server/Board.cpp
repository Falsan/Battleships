#include "Board.h"

board::board()
{

}

board::~board()
{

	m_board.clear();


}

void board::createBoard()
{
	for (int i = 0; i < m_boardSize; i++)
	{
		m_board.push_back(new Cell);
	}
}