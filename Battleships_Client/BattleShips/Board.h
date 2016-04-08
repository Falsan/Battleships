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
	void setCell(int type, int x, int y);
	void makeShip(int size, int orientation, std::pair<int, int> origin);
	std::vector<Cell*> getBoard() { return board; }

protected:

private:

	std::vector<Cell*> board;
	std::vector<Ship*> ships;
};