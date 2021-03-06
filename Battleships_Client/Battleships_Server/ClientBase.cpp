#include "ClientBase.h"
#include "CellTypesLoc.h"



ClientBase::ClientBase()
{
	for (int i = 0; i < 100; i++)
	{
		m_PlayersBoard.push_back(new Cell);
	}
}


//Receving a board from the player 
void ClientBase::setUpBoard(std::vector <int> _ShipPos)
{

	//place all the locations that we have receved on to the board
	int counter = 0;
	int shipCounter = 0;
	for (auto it = m_PlayersBoard.begin(); it != m_PlayersBoard.end(); it++)
	{

		if (shipCounter < 15)
		{
			if (counter == _ShipPos[shipCounter])
			{
				(*it)->setType(CELLTYPES::SHIP);
				shipCounter++;
			}
		}

		counter++;
	}

	Draw::drawBoard(m_PlayersBoard);
}