#ifndef _BOARD_
#define _BOARD_


#include <array>
#include "Cell.h"


class Board
{
public:
	Board();
	~Board();
	void createBoard();
	std::array<std::array<Cell*,10 >, 10> m_board;

	
};

#endif