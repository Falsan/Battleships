#include "Game.h"
#include "GamePhase.h"
#include <SFML\Network.hpp>


GameBase::GameBase(Client* _playerOne/*, Client * _playerTwo*/)
{
	//once the game is initalized marks the two players in the game mode
	setPlayerOne(_playerOne);
	//setPlayerTwo(_playerTwo);
}
