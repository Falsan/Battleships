#include "BoardManager.h"

BoardManager::BoardManager()
{
	board = new Board;
}

BoardManager::~BoardManager()
{
	delete board;
}

bool BoardManager::playerPlaceShip(Ship* _ship)
{
	if (testShip(_ship))
	{
		putShipOnBoard(_ship);
		Draw::drawBoard(board->getBoard());
		return true;
	}
	else
	{
		Draw::drawBoard(board->getBoard());
		return false;
	}

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

bool BoardManager::testShip(Ship* _ship)
{
	int error = 0; 
	int x =_ship->getPos().first;
	int y = _ship->getPos().second;
	//make sure none of the ship falls out of bounds
	for (int i = 0; i < _ship->getSize(); i++)
	{
		switch (_ship->getOrientation)
		{
		case 0:
			if (!testBound((x - i), y))
			{
				error++;
			}
			break;
		case 1:
			if(!testBound(x, (y + i)))
			{
				error++;
			}
			break;
		case 2:
			if(!testBound((x + i), y))
			{
				error++;
			}
			break;
		case 3: 
			if(!testBound(x, (y - i)))
			{
				error++;
			}
			break;
		}
	}

	//Test if any of the ships collide
	for (int i = 0; i < _ship->getSize(); i++)
	{
		switch (_ship->getOrientation)
		{
		case 0:
			if (board->getCell((x - i), y)->getType() == CellTypes::SHIP)
			{
				error++;
			}
			break;
		case 1:
			if (board->getCell(x, (y + i))->getType() == CellTypes::SHIP)
			{
				error++;
			}
			break;
		case 2:
			if (board->getCell((x + i),y)->getType() == CellTypes::SHIP)
			{
				error++;
			}
			break;
		case 3:
			if (board->getCell(x, (y - i))->getType() == CellTypes::SHIP)
			{
				error++;
			}
			break;
		}
	}


	if (error > 0)
	{
		return false;
	}
	else
	{
		return true;
	}
}

/*
0 - north
1 - East
2 - South
3 - West
*/



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

void BoardManager::putShipOnBoard(Ship * _ship)
{
	int x = _ship->getPos().first;
	int y = _ship->getPos().second;

	for (int i = 0; i < _ship->getSize(); i++)
	{
		switch (_ship->getOrientation)
		{
		case 0:
			board->getCell(x - i, y)->setType(CellTypes::SHIP);
			break;
		case 1:
			board->getCell(x, y + i)->setType(CellTypes::SHIP);
			break;
		case 2:
			board->getCell(x + i, y)->setType(CellTypes::SHIP);
			break;
		case 3:
			board->getCell(x, y - i)->setType(CellTypes::SHIP);
			break;
		}
	}
}

bool BoardManager::shootBoard(std::pair<int, int> _shot, std::vector <Cell*> _board)
{
	int loc = (10 * _shot.first) + _shot.second;
	if (_board[loc]->getType() == 0)
	{
		return true;
	}
	else if (_board[loc]->getType() == 1)
	{
		return false;
	}
}