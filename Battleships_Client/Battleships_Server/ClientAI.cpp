#include "ClientAI.h"
#include <stdlib.h>
#include <time.h>
#include "Celltypes.h"
#include "Board.h"
#include "Cell.h"


AIClient::AIClient(Board* _PlayersBoard,int difficulty)
{
	isAI = true;
	srand(time(NULL));
	

	//for every cell on the board
	for (int x = 0; x < 10; x++)
	{
		for (int y = 0; y < 10; y++)
		{
			float arroundVal = 0;
			int TestCell = (x * 10) + y;
			//test every cell around it
			for (int i = -4; i < 5; i++)
			{
				for (int j = -4; j < 5; j++)
				{
					int testPos = (10 + i) + j;
					//while not out of bound low
					if ((TestCell - testPos) > 0)
					{
						//while not out of bounds high
						if (TestCell + testPos < 100)
						{
							//while not ourselves
							if (i + j != 0)
							{
								if (_PlayersBoard->getBoard()[arroundVal]->getType() == CellTypes::SHIP)
								{
									arroundVal + difficulty;
								}
								
							}
							else
							{
								if (_PlayersBoard->getBoard()[arroundVal]->getType() == CellTypes::SHIP)
								{
									arroundVal + difficulty* 10;
								}
							}
						}
					}
				}
			}
			_PlayersBoard->getBoard()[TestCell]->setShotChance(arroundVal);
		}
	}
	
}

AIClient::~AIClient()
{

}

int AIClient::AIShoot()
{
	int posable = 0;
	Cell * CellHOLD = nullptr;
	bool shoot;
	int counter = 5;
	int cellCounter = 0;
	
	//loop through till we find a square to shoot
	while (!CellHOLD)
	{
		//loop through all elements on the board
		for (auto it = getOppenent()->getPlayersBoard().begin(); it != getOppenent()->getPlayersBoard().end(); it++)
		{
			if (((*it)->getType() != CellTypes::MISS) || ((*it)->getType() != CellTypes::HIT))
			{
				if ((*it)->getShotChance > rand() % 100 + 1)
				{
					CellHOLD = (*it);
					// if we have found a cell to shoot
					shoot = true;
					counter = 5;
				}

				if (shoot == true)
				{
					//detract from the counter,
					--counter;
					if (counter < 0)
					{
						//if we have found a cell and the counter has not reset exit the loop
						break;
					}
				}
			}
			cellCounter++;
		}
	}

	if (getOppenent()->getPlayersBoard()[cellCounter]->getType() == CellTypes::SHIP)
	{
		getOppenent()->getPlayersBoard()[cellCounter]->setType(CellTypes::HIT);
	}
	else if(getOppenent()->getPlayersBoard()[cellCounter]->getType() == CellTypes::EMPTY)
	{
		getOppenent()->getPlayersBoard()[cellCounter]->setType(CellTypes::MISS);
	}
	else
	{

	}

	return cellCounter;
}
