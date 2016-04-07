#pragma once
#include "Board.h"
#include "Ship.h"

class BoardManager
{
public:
	BoardManager();
	~BoardManager();

	void playerPlaceShip(int size);
	bool testBound(int x, int y);
	bool testShip(int x, int y);
	//std::vector<std::pair<int, int>> getOrientation(Ship* ship);
	void putShipOnBoard();
	static int shootBoard(std::pair<int, int>, std::vector <Cell*>);

protected:

private:

	Board* board;
	std::vector<Ship*> ships;
};
