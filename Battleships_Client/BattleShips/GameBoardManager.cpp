#include "BoardManager.h"

BoardManager::BoardManager()
{
	board = new Board;
}

BoardManager::~BoardManager()
{
	delete board;
}

void BoardManager::playerPlaceShip(int size)
{

}

bool BoardManager::testBound(int x, int y)
{
	if (x > 9 || x < 0)
	{
		return false;
	}
	else if (y > 9 || y < 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

bool BoardManager::testShip(int x, int y)
{

	return true;
}

//std::vector<std::pair<int, int>> BoardManager::getOrientation(Ship* ship)
//{

	//if (ship->getOrientation() == 0)
	//{

	//}
	//if (board->getBoard()[ship->getPos()]->getPos() == 0)
	//{

	//}
	//if (ship->getSize());

//}

void BoardManager::putShipOnBoard()
{

}

int BoardManager::shootBoard(std::pair<int,int> _shot, std::vector <Cell*> _board)
{
	int loc = (1 * _shot.first) + _shot.second;

	return _board[loc]->getType();


}