#ifndef _BOARD_
#define _BOARD_


#include <array>
#include "Cell.h"
#include "GameData.h"

class Board
{
public:
	Board(gameData * _GD);
	~Board();
	void createBoard();
	std::array<std::array<Cell*,10 >, 10> m_board;
	gameData * m_GD;
	
};

#endif