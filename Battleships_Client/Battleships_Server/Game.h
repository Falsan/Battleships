#pragma once
#include "Client.h"
#include <vector>
#include "Cell.h"
#include "GamePhase.h"
#include "Client.h"




class ServerClient;
class GameBase
{
public:
	GameBase(ServerClient* _playerOne, ServerClient * _playerTwo);
	~GameBase() = default;

	ServerClient * getPlayerOne() { return PlayerOne; };
	ServerClient * getPlayerTwo() { return PlayerTwo; };
	bool getCurrentTurn() { return currentPlayerTurn; }
	int getCurrentPhase() { return currentPhase; }

	void setPlayerOne(ServerClient * _in) { PlayerOne = _in; };
	void setPlayerTwo(ServerClient * _in) { PlayerTwo = _in; };
	void setCurrentTurn(bool _in) { currentPlayerTurn = _in; }
	void setCurrentPhase(int _in) { currentPhase = _in; }

	virtual bool update(sf::Packet _inPacket, ServerClient * _inClient) = 0;

	virtual void input(int _in) = 0;
	virtual int outPut() = 0;


private:

	ServerClient * PlayerOne;
	ServerClient * PlayerTwo;
	int currentPhase = GAMEPHASE::SETUP; 
	int currentPlayerTurn = 0;
};