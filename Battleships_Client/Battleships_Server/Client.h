#pragma once
#include <string>
#include <SFML\Network.hpp>
#include <vector>

#include "Cell.h"
#include <chrono>
#include "Game.h"

class BattleShipsGame;

class ServerClient
{
public:
	ServerClient();
	~ServerClient() = default;

	void setUpBoard(std::vector <int> _ShipPos);

	int getClientID() { return clientID; }
	int getTimeOuts() { return timeOuts; }
	std::chrono::steady_clock::time_point getLastPing() { return lastPingValue; }
	std::chrono::steady_clock::time_point getLastPong() { return lastPongValue; }
	sf::TcpSocket* getSocket() { return socket; }
	bool getBoardSet() { return boardSet; };
	std::vector <Cell*> getPlayersBoard() { return m_PlayersBoard; }
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
	void setPlayersBoard(std::vector <Cell*> _in) { m_PlayersBoard = _in; }
	void setTakeTurn(bool _in) { takeTurn = _in; }
	void setNickName(std::string _in) { nickName = _in; }
	void setGame(BattleShipsGame * _in) { currentGame = _in; }
	void setDuration(int _in) { duration = _in; }
	void setOponent(ServerClient * _in) { opponent = _in; }

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
	std::vector <Cell*> m_PlayersBoard;
	bool takeTurn = false;
	std::string nickName = "NULL";

	ServerClient * opponent;

	BattleShipsGame * currentGame;

};