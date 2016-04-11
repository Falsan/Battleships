#include "BattleShipsGame.h"
#include "CellTypesLoc.h"



BattleShipsGame::BattleShipsGame(Client* _playerOne/*, Client * _playerTwo*/):GameBase(_playerOne/*, _playerTwo*/)
{

}

void BattleShipsGame::update(sf::Packet _inPacket, Client * _inClient)
{
	sf::Packet outPacketPlayer;
	sf::Packet outPacketOponent;
	std::string out;
	std::string outOponent;
	std::pair<int, int> pos;
	//take out any board pos request
	_inPacket >> pos.first;
	_inPacket >> pos.second;
	int loc = 10;
	int shotPos = (loc*pos.first) + pos.second;



	//get the type of cell that the player has shot
	int shot = _inClient->getOppenent()->getPlayersBoard()[shotPos]->getType();
	switch (shot + 2)
	{
	case 2:
		//Tell the player that they have missed
		out = "Shot missed";
		//inform the oponent that it is now there turn
		outOponent = "TURN";
		//set the value stroed in that cell to miss
		_inClient->getOppenent()->getPlayersBoard()[shotPos]->setType(CELLTYPES::EMPTY);

		break;
	case 3:
		//Tell the player that they have hit
		out = "HIT";
		//tell the oponent that it is still no there turn
		outOponent = "NULL";
		//set the value in the cell to a hit ship
		_inClient->getOppenent()->getPlayersBoard()[shotPos]->setType(CELLTYPES::HITSHIP);
		break;
		//these value can only be reached if a player attempts to shoot the same cell multiple times
	case 4:
	case 5:
	case 6:
		out = "You already shot there";
		outOponent = "NULL";

		break;
	}

	//Send out our results
	outPacketPlayer << out;
	outPacketOponent << outOponent;
	_inClient->getSocket()->send(outPacketPlayer);
	_inClient->getOppenent()->getSocket()->send(outPacketOponent);
}
/*
0 = empty
1 = ship
2 = shot
3 = shot + ship
*/

void BattleShipsGame::input(int _in) 
{

}

int BattleShipsGame::outPut()
{

	return 1;
}