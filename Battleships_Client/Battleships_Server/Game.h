#pragma once
#include "Client.h"
#include <vector>
#include "Cell.h"
#include "GamePhase.h"
#include "Client.h"




class Client;
class GameBase
{
public:
	GameBase(Client* _playerOne/*, Client * _playerTwo*/);
	~GameBase() = default;

	Client * getPlayerOne() { return PlayerOne; };
	Client * getPlayerTwo() { return PlayerTwo; };
	bool getCurrentTurn() { return currentPlayerTurn; }
	int getCurrentPhase() { return currentPhase; }

	void setPlayerOne(Client * _in) { PlayerOne = _in; };
	void setPlayerTwo(Client * _in) { PlayerTwo = _in; };
	void setCurrentTurn(bool _in) { currentPlayerTurn = _in; }
	void setCurrentPhase(int _in) { currentPhase = _in; }

	virtual void update(sf::Packet _inPacket, Client * _inClient) = 0;

	virtual void input(int _in) = 0;
	virtual int outPut() = 0;


private:

	Client * PlayerOne;
	Client * PlayerTwo;
	int currentPhase = GAMEPHASE::SETUP; 
	int currentPlayerTurn = 0;
};