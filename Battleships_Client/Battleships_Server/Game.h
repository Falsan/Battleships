#pragma once
#include "Client.h"
#include <vector>
#include "Cell.h"
#include "GamePhase.h"
#include "Client.h"


class Client;
class BattleShipsGame
{
public:
	BattleShipsGame(Client* _playerOne, Client * _playerTwo);
	~BattleShipsGame() = default;

	Client * getPlayerOne() { return PlayerOne; };
	Client * getPlayerTwo() { return PlayerTwo; };
	std::vector<Cell*> getGameBoard() { return gameBoard; };
	bool getCurrentTurn() { return currentTurn; }
	int getCurrentPhase() { return currentPhase; }

	void setPlayerOne(Client * _in) { PlayerOne = _in; };
	void setPlayerTwo(Client * _in) { PlayerTwo = _in; };
	void setGameBoard(std::vector<Cell*> _inBoard) { gameBoard = _inBoard; };
	void setCurrentTurn(bool _in) { currentTurn = _in; }
	void setCurrentPhase(int _in) { currentPhase = _in; }

	void update();



private:
	std::vector<Cell*> gameBoard;
	Client * PlayerOne;
	Client * PlayerTwo;
	int currentPhase = GAMEPHASE::SETUP; 
	bool currentTurn = true;
};