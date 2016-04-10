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
	bool handelShot(int player, int val, std::pair<int, int> loc);

	bool createFlotila(int AC = 1,int BS = 1,int SM = 1,int DES = 1, int PB = 1);

	Board* startUp();

	std::vector<Ship*> getListOfShips() { return m_listOfShips; }
	void setListOfShips(std::vector<Ship*> _in) { m_listOfShips = _in; }
	void addShipToList(Ship*_in) { m_listOfShips.push_back(_in); }
	void setBoard(std::vector<Cell*>);

	Ship* getShipFromList(int _in) { return m_listOfShips[_in]; }




protected:

private:
	std::vector<Ship*> m_listOfShips;
	Board* m_board;
	Board* m_enemyBoard;
	std::vector<Ship*> ships;
};
