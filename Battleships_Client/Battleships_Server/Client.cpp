#include "Client.h"
#include "Celltypes.h"
#include "LoadIn.h"

ServerClient::ServerClient()
{
	for (int i = 0; i < 100; i++)
	{
		m_AIBoard.push_back(new Cell);
	}

}

void ServerClient::setAINodes(int difficulty)
{
	std::vector<Cell*> surroundCells;
	isAI = true;
	srand(time(NULL));
	int shipCounter = 0;



	for (int k = 0; k < 10; ++k)
	{
		for (int l = 0; l < 10; ++l)
		{
			//For each item around the current cell 
			for (int i = -1; i < 2; i++)
			{
				for (int j = -1; j < 2; j++)
				{
					//While not the cell itself 
					if (!((i == 0) && (j == 0)))
					{
						//while not out of bounds lower 
						if ((i + k >= 0) && (l + j >= 0))
						{

							//and now out of bound upper
							if ((i + k < 10) && (l + j < 10))
							{
								//Place the element on to our list of surround cells
								if (getPlayersBoard()[((k + i) * 10) + (l + j)]->getType() == CellTypes::SHIP)
								{
									surroundCells.push_back(getPlayersBoard()[((k + i) * 10) + (l + j)]);
								}
							}
						}
					}
				}
			}
			if (surroundCells.size() == 0)
			{
				getPlayersBoard()[(k * 10) + l]->setShotChance(difficulty);
			}
			for (auto it = surroundCells.begin(); it != surroundCells.end(); it++)
			{

				getPlayersBoard()[(k * 10) + l]->setShotChance(getPlayersBoard()[(k * 10) + l]->getShotChance() + difficulty);

			}

			surroundCells.clear();

		}






		//
		////for every cell on the board
		//for (int x = 0; x < 10; x++)
		//{
		//	for (int y = 0; y < 10; y++)
		//	{
		//		float arroundVal = 0;
		//		int TestCell = (x * 10) + y;
		//		//test every cell around it

		//		if (getPlayersBoard()[arroundVal]->getType() != CellTypes::SHIP)
		//		{
		//		
		//			for (int i = -4; i < 5; i++)
		//			{
		//				for (int j = -4; j < 5; j++)
		//				{
		//					int testPos = (14 + i) + j;
		//					//while not out of bound low
		//					if ((TestCell - testPos) > 0)
		//					{
		//						//while not out of bounds high
		//						if (TestCell + testPos < 100)
		//						{
		//							//while not ourselves
		//							if (i + j != 0)
		//							{
		//								surroundCells.push_back(getPlayersBoard()[arroundVal]);
		//							}
		//						}
		//					}
		//				}
		//			}

		//			for (auto it = surroundCells.begin(); it != surroundCells.end(); it++)
		//			{
		//				if ((*it)->getType() == CellTypes::SHIP)
		//				{
		//					getPlayersBoard()[arroundVal]->setShotChance(getPlayersBoard()[arroundVal]->getShotChance() + difficulty);
		//				}
		//			}

		//			surroundCells.clear();
		//		}
		//		else
		//		{
		//			getPlayersBoard()[arroundVal]->setShotChance(difficulty * 10);
		//		}
		//	}
		//}

	}
}



bool ServerClient::AIShoot(ServerClient* _openent)
{
	int posable = 0;
	Cell * CellHOLD = nullptr;
	bool shoot = false;
	int counter = 5;
	int cellCounter = 0;

	//loop through till we find a square to shoot
	do
	{
		int size = _openent->getPlayersBoard().size();
		cellCounter = 0;

		Draw::drawDebugBoard(_openent->getPlayersBoard());

		//loop through all elements on the board
		for (int it = 0; it < size; it++)
		{
			if ((_openent->getPlayersBoard()[it]->getType() != CellTypes::MISS) || (_openent->getPlayersBoard()[it]->getType() != CellTypes::HIT))
			{
				if (_openent->getPlayersBoard()[it]->getShotChance() > rand() % 100 + 1)
				{
					CellHOLD = _openent->getPlayersBoard()[it];
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
	} while (!CellHOLD);

	if (getOppenent()->getPlayersBoard()[cellCounter]->getType() == CellTypes::SHIP)
	{
		getOppenent()->getPlayersBoard()[cellCounter]->setType(CellTypes::HIT);
		return true;
	}
	else if (getOppenent()->getPlayersBoard()[cellCounter]->getType() == CellTypes::EMPTY)
	{
		getOppenent()->getPlayersBoard()[cellCounter]->setType(CellTypes::MISS);
		lastHit = cellCounter;
		return false;
	}
	else
	{
		return true;
	}

}

void ServerClient::AILoadLevel()
{
	m_AIBoard = LoadIn::loadFile("Level1", m_AIBoard);

}