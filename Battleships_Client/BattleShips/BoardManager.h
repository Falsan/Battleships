#pragma once
#include "Board.h"
#include "Ship.h"
#include "DrawBoard.h"

class BoardManager
{
public:
	BoardManager();
	~BoardManager();

	bool playerPlaceShip(Ship*);
	bool testBound(int x, int y);
	bool testShip(Ship* _ship);
	//std::vector<std::pair<int, int>> getOrientation(Ship* ship);
	void putShipOnBoard(Ship * _inShip);
	bool shootBoard(std::pair<int, int>);

	void startUp();


	void loadBoard(std::vector<int>);

protected:

private:

	Board* board;
	std::vector<Ship*> ships;
};
