#include "BattleShipsGame.h"
#include "Celltypes.h"

BattleShipsGame::BattleShipsGame(ServerClient* _playerOne, ServerClient * _playerTwo):GameBase(_playerOne, _playerTwo)
{

}

//The update function for the battle ships game, here shots are tested, in future this could be replaced with
//othe update functions for devising a new game
bool BattleShipsGame::update(sf::Packet _inPacket, ServerClient * _inClient)
{
	
	int x;
	int y;

	_inPacket >> x;
	_inPacket >> y;

	int loc = (x * 10) + y;



	if (!_inClient->isAI)
	{
		int TestCell = _inClient->getOppenent()->getAIBoard()[loc]->getType();

		switch (TestCell)
		{
		case::CellTypes::EMPTY:
			_inClient->getOppenent()->getAIBoard()[loc]->setType(CellTypes::MISS);
			return false;
			break;
		case::CellTypes::HIT:
			return true;
			break;
		case::CellTypes::SHIP:
			_inClient->getOppenent()->getAIBoard()[loc]->setType(CellTypes::HIT);
			return true;
			break;
		case::CellTypes::MISS:
			return true;
			break;
		}
	}
	else
	{
		int TestCell = _inClient->getOppenent()->getPlayersBoard()[loc]->getType();
		switch (TestCell)
		{
		case::CellTypes::EMPTY:
			_inClient->getOppenent()->getPlayersBoard()[loc]->setType(CellTypes::MISS);
			return false;
			break;
		case::CellTypes::HIT:
			return true;
			break;
		case::CellTypes::SHIP:
			_inClient->getOppenent()->getPlayersBoard()[loc]->setType(CellTypes::HIT);
			return true;
			break;
		case::CellTypes::MISS:
			return true;
			break;
		}
	}
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