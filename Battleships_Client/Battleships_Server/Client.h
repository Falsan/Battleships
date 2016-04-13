#pragma once
#include <string>
#include <SFML\Network.hpp>
#include <vector>

#include "Cell.h"
#include <chrono>
#include "Game.h"
#include "ClientBase.h"

class BattleShipsGame;

class ServerClient : public ClientBase
{
public:
	ServerClient(std::vector<Cell*>, int difficulty, bool dudBoard);
	~ServerClient() = default;


	int getClientID() { return clientID; }
	int getTimeOuts() { return timeOuts; }
	std::chrono::steady_clock::time_point getLastPing() { return lastPingValue; }
	std::chrono::steady_clock::time_point getLastPong() { return lastPongValue; }
	sf::TcpSocket* getSocket() { return socket; }
	bool getBoardSet() { return boardSet; };

	bool getTakeTurn() { return takeTurn; }
	std::string getNickName() { return nickName; }
	BattleShipsGame * getGame() { return currentGame; }
	int getDuration() { return duration; }
	ServerClient* getOppenent() { return opponent; };


	void setClientID(int _in) { clientID = _in; }
	void setTimeOuts(int _in) { timeOuts = _in; }

	void setLastPingVal(std::chrono::steady_clock::time_point _in) { lastPingValue = _in; }
	void setLastPongVal(std::chrono::steady_clock::time_point _in) { lastPongValue = _in; }

	void setSocket(sf::TcpSocket* _in) { socket = _in; }
	void setBoardSet(bool _in) { boardSet = _in; }

	void setTakeTurn(bool _in) { takeTurn = _in; }
	void setNickName(std::string _in) { nickName = _in; }
	void setGame(BattleShipsGame * _in) { currentGame = _in; }
	void setDuration(int _in) { duration = _in; }
	void setOponent(ServerClient * _in) { opponent = _in; }


	
	void setAIBoard(std::vector<Cell*> _in) { m_AIBoard = _in; }
	std::vector<Cell*> getAIBoard() { return m_AIBoard; }

	bool AIShoot();

	void AILoadLevel();

	std::vector <Cell*> m_AIBoard;



private:
	// the Id used to identify the user
	int clientID;

	//the number of times the user has failed a heart beat test
	int timeOuts = 0;
	std::chrono::steady_clock::time_point lastPingValue;
	std::chrono::steady_clock::time_point lastPongValue;
	float duration;

	sf::TcpSocket* socket;
	bool boardSet = false;

	bool takeTurn = false;
	std::string nickName = "NULL";

	ServerClient * opponent;

	BattleShipsGame * currentGame;

};



