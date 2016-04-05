#include "Game.h"
#include <SFML\Network.hpp>

BattleShipsGame::BattleShipsGame(Client* _playerOne, Client * _playerTwo)
{
	//once the game is initalized marks the two players in the game mode
	setPlayerOne(_playerOne);
	setPlayerTwo(_playerTwo);


}

void BattleShipsGame::update()
{
	sf::Packet s;
	std::string HOLD;
	bool playing = true;
	//test to ensure that both players are still connected
	
	//If one has left 
	//set phase to reslove


	while (!playing)
	{
		switch (currentPhase)
		{
		case GAMEPHASE::SETUP:
			//Make the gameboard with function from the static lib
			//setGameBoard();

			HOLD = "set up board ";
			s << HOLD;

			getPlayerOne()->getSocket()->send(s);
			getPlayerOne()->getSocket()->send(s);

			if (!(getPlayerOne()->getBoardSet()) || !(getPlayerTwo()->getBoardSet()))
			{
				//Hold and wait for boads to be settup
			}
			else
			{
				currentPhase = GAMEPHASE::TURNONE;
			}
			break;
		case GAMEPHASE::TURNONE:

			//If the player has sent a turn
			if (getPlayerOne()->getTakeTurn())
			{
				if (getPlayerOne()->GetTurnAction()->getActedUpon())
				{

					//Use the shot held in turn with the static lib to shoot at the board;
					currentPhase = GAMEPHASE::TESTWIN;
					getPlayerOne()->GetTurnAction()->setActedUpon(true);
				}




				break;
		case GAMEPHASE::TURNTWO:


			//If the player has sent a turn
			if (getPlayerTwo()->getTakeTurn())
			{
				if (getPlayerTwo()->GetTurnAction()->getActedUpon())
				{
					//Use the shot held in turn with the static lib to shoot at the board;
					currentPhase = GAMEPHASE::TESTWIN;
					getPlayerTwo()->GetTurnAction()->setActedUpon(true);
				}
			}

			break;
		case GAMEPHASE::RESOLVEGAME:

			//send message to remaining player congratulating them on there win and asking if they would like to save


			break;
		case GAMEPHASE::TESTWIN:

			//Static lib board testing here



			if (getCurrentTurn())
			{
				currentPhase = GAMEPHASE::TURNTWO;
				setCurrentTurn(false);
			}
			else
			{
				currentPhase = GAMEPHASE::TURNONE;
				setCurrentTurn(true);
			}
			break;
			}
		}
	}
}