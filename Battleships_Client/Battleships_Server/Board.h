#ifndef _BOARD_
#define _BOARD_


#include <array>
#include "Cell.h"
#include "GameData.h"

class board
{
public:
	board(gameData * _GD);
	~board();
	void createBoard();
	std::array<std::array<Cell*,10 >, 10> m_board;
	gameData * m_GD;
	
};

#endif