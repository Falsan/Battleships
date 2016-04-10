#include "BoardManager.h"
#include <iostream>
#include "Validation.h"
#include <iostream>
#include <string>
#include "LoadIn.h"

BoardManager::BoardManager()
{
	m_board = new Board;
	m_enemyBoard = new Board;
}

BoardManager::~BoardManager()
{
	delete m_board;
	delete m_enemyBoard;
}

//handels the creation of the board
Board* BoardManager::startUp()
{
	bool repeat = false;
	int responce;
	std::string fileName;
	do
	{
		repeat = false;
		std::cout << "Load ship configuration or start from scratch?" << std::endl << "1. Load" << std::endl << "2. Create flotila " << std::endl;
		responce = Valid::validIn(3, 0);

		if (responce == 1)
		{
			std::cout << "Please enter the name of the file you wish to load" << std::endl;
			std::getline(std::cin, fileName);

			auto loaded = LoadIn::loadFile(fileName);
			//if file has loaded
			if (loaded[0]->getType() == 9)
			{
				repeat = true;
				std::cout << "Error file not found" << std::endl;
			}
			{
				setBoard(loaded);
			}
		}
		else if (responce == 2)
		{

			//Fills out our ship list and adds them to the board
			if (createFlotila())
			{
				break;
			}
			//Make and add ships to level

		}
	} while (repeat = true);
	//send board
	return m_board;
}

void BoardManager::setBoard(std::vector<Cell*> _inVec)
{
	
	for (int i = 0 ; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			int loc = (10 * i) + j;

			m_board->getCell(loc)->setType(_inVec[loc]->getType());
		}
	}


}

//Unless otherwise requested creates one of each ship and adds them to our list
bool BoardManager::createFlotila(int AC, int BS, int SM, int DES, int PB)
{
	Ship* holdShip = new Ship;
	std::vector<int> listOfVals;
	std::pair<int, int> pos;
	int rot;
	char rotHold;

	for (int i = 0; i < AC; i++)
	{
		listOfVals.push_back(5);
	}
	for (int i = 0; i < BS; i++)
	{
		listOfVals.push_back(4);
	}
	for (int i = 0; i < SM; i++)
	{
		listOfVals.push_back(3);
	}
	for (int i = 0; i < DES; i++)
	{
		listOfVals.push_back(2);
	}
	for (int i = 0; i < PB; i++)
	{
		listOfVals.push_back(1);

	}
	
	int sumOfShips = ((AC*5) + (BS*4) + (SM*3) + (DES*2) + (PB*1));

	if (sumOfShips > 100)
	{
		std::cout << "Error: not enough space on board for requested ships" << std::endl;
		return false;
	}
 
	for (auto it = listOfVals.begin(); it != listOfVals.end(); it++)
	{
		Draw::drawBoard(m_board->getBoard());
		do
		{
		std::string shipType;
		std::cout << std::endl << "Select were to place [";

		switch ((*it))
		{
		case 1:
			shipType = "Patrol boat (1)";
			break;
		case 2:
			shipType = "Destroyer (2)";
			break;
		case 3:
			shipType = "Submarine (3)";
			break;
		case 4:
			shipType = "BattleShip (4)";
			break;
		case 5:
			shipType = "Aircraft carrier (5)";
			break;

		}
		std::cout << shipType << "]" << std::endl;

		std::cout << "X position:";
		std::cin >> pos.first;
		std::cout << std::endl << "Y position:";
		std::cin >> pos.second;
		do
		{
			std::cout << "facing N,S,E,W?" << std::endl;
			std::cin >> rotHold;
			rotHold = toupper(rotHold);

			switch (rotHold)
			{
			case 'N':
				rot = 0;
				break;
			case 'E':
				rot = 1;
				break;
			case 'S':
				rot = 2;
				break;
			case 'W':
				rot = 3;
				break;
			default:
				rot = 4;
				break;
			}

			rotHold = 0;
		} while (rot == 4);

		holdShip->setSize((*it));
		holdShip->setOrientation(rot);
		holdShip->setPos(pos);		
		} while (!playerPlaceShip(holdShip));
		addShipToList(holdShip);
	}
	return true;
}


bool BoardManager::playerPlaceShip(Ship* _ship)
{
	if (testShip(_ship))
	{
		putShipOnBoard(_ship);
	//	Draw::drawBoard(m_board->getBoard());
	//	Draw::drawBoard(m_enemyBoard->getBoard());
		return true;
	}
	else
	{
		std::cout << "Error placing ship please retry" << std::endl;
		//Draw::drawBoard(m_board->getBoard());
		//Draw::drawBoard(m_enemyBoard->getBoard());
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
		switch (_ship->getOrientation())
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
	//If the ship has not fallen out of bounds
	if (error <= 0)
	{
		//Test if any of the ships collide
		for (int i = 0; i < _ship->getSize(); i++)
		{
			switch (_ship->getOrientation())
			{
			case 0:
				if (m_board->getCell((x - i), y)->getType() == CellTypes::SHIP)
				{
					error++;
				}
				break;
			case 1:
				if (m_board->getCell(x, (y + i))->getType() == CellTypes::SHIP)
				{
					error++;
				}
				break;
			case 2:
				if (m_board->getCell((x + i), y)->getType() == CellTypes::SHIP)
				{
					error++;
				}
				break;
			case 3:
				if (m_board->getCell(x, (y - i))->getType() == CellTypes::SHIP)
				{
					error++;
				}
				break;
			}
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

void BoardManager::putShipOnBoard(Ship * _ship)
{
	int x = _ship->getPos().first;
	int y = _ship->getPos().second;

	for (int i = 0; i < _ship->getSize(); i++)
	{
		switch (_ship->getOrientation())
		{
		case 0:
			m_board->getCell(x - i, y)->setType(CellTypes::SHIP);
			break;
		case 1:
			m_board->getCell(x, y + i)->setType(CellTypes::SHIP);
			break;
		case 2:
			m_board->getCell(x + i, y)->setType(CellTypes::SHIP);
			break;
		case 3:
			m_board->getCell(x, y - i)->setType(CellTypes::SHIP);
			break;
		}
	}
}

bool BoardManager::handelShot(int player,int val, std::pair<int,int> inLoc)
{
	int Loc = ((10 * inLoc.first) + inLoc.second);

	//If the player is the one who shot
	if(player == 0)
	{
		m_enemyBoard->getBoard()[Loc]->setType(val);
		return true;
	}
	else if (player == 1)//if the opponent shot
	{
		m_board->getBoard()[Loc]->setType(val);
		return true;
	}//shot was inccorect, shot an already shot spot, retry
	else
	{
		return false;
	}
	return false;
}
