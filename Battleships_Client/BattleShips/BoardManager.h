#pragma once
#include "Board.h"
#include "Ship.h"
#include "DrawBoard.h"

class BoardManager
{
public:
	BoardManager();
	~BoardManager();


	//std::vector<std::pair<int, int>> getOrientation(Ship* ship);

	bool handelShot(int player, int val, std::pair<int, int> loc);

	

	Board* startUp();

	std::vector<Ship*> getListOfShips() { return m_listOfShips; }

	Board * getBoardObject() { return m_board; }

	Ship* getShipFromList(int _in) { return m_listOfShips[_in]; }
	void setBoard(std::vector<Cell*>);

	std::string boardToSend(std::vector<Cell*> _inVec);

	std::vector<int> getCompBoard() { return m_compiledBoard; };

	std::vector<int> m_compiledBoard;
protected:

private:
	void putShipOnBoard(Ship * _inShip);
	bool playerPlaceShip(Ship*);
	bool testBound(int x, int y);
	bool testShip(Ship* _ship);
	void setListOfShips(std::vector<Ship*> _in) { m_listOfShips = _in; }
	void addShipToList(Ship*_in) { m_listOfShips.push_back(_in); }

	bool createFlotila(int AC = 1,int BS = 1,int SM = 1,int DES = 1, int PB = 1);


	std::vector<Ship*> m_listOfShips;
	Board* m_board;
	Board* m_enemyBoard;
	std::vector<Ship*> ships;
};
