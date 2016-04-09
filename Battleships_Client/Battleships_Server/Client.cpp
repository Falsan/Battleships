#include "Client.h"
#include "Celltypes.h"

//Receving a board from the player 
void Client::setUpBoard(std::vector <std::pair<int, int>> _ShipPos)
{

	//place all the locations that we have receved on to the board

	for (auto it = _ShipPos.begin(); it != _ShipPos.end(); it++)
	{
		int loc = 10;
		m_PlayersBoard[(loc*(*it).first) + (*it).second]->setType(CellTypes::SHIP);
	}

}