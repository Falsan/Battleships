#include "Game.h"
#include "GamePhase.h"
#include <SFML\Network.hpp>


GameBase::GameBase(ServerClient* _playerOne,ServerClient * _playerTwo)
{
	//once the game is initalized marks the two players in the game mode
	setPlayerOne(_playerOne);
	setPlayerTwo(_playerTwo);
}
