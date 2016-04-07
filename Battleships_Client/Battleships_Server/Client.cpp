#include "Client.h"

//Receving a board from the player 
std::vector <Cell*> Client::setUpBoard(std::vector <std::pair<int, int>> _ShipPos)
{
	int loc = 1;
	//place all the locations that we have receved on to the board

	for (auto it = _ShipPos.begin(); it != _ShipPos.end(); it++)
	{
		m_PlayersBoard[(loc*(*it).first) + (*it).second];
	}	

	return m_PlayersBoard;
}