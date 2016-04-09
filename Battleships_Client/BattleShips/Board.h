#pragma once

#include <vector>
#include "Cell.h"
#include "Celltypes.h"
#include "Ship.h"

class Board
{
public:

	Board();
	~Board();
	Cell* getCell(int x, int y);
	Cell* getCell(int loc);
	void setCell(int type, int x, int y);
	void setCell(int loc, int _in);
	
	std::vector<Cell*> getBoard() { return m_board; }

protected:

private:

	std::vector<Cell*> m_board;
	std::vector<Ship*> ships;
};
