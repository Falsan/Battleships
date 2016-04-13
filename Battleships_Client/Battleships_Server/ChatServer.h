#pragma once

#include <iostream>
#include <SFML\Network.hpp>
#include <vector>
#include "Client.h"
#include "Game.h"
#include "BattleShipsGame.h"
#include <memory>
#include "ChatLog.h"


typedef std::chrono::high_resolution_clock Clock;

class ChatServer
{
public:
	ChatServer(std::vector<ServerClient*> _listOfClients, sf::SocketSelector& _selector);
	~ChatServer() = default;

	const int SERVER_PORT = 53000;

	void removeClientWithSocket(sf::TcpSocket* _id);
	ServerClient * findClientWithID(int _ID);
	void runServer();
	void bindServerPort(sf::SocketSelector& selector, sf::TcpListener& listerner);
	void listen(sf::SocketSelector& selector, std::vector<ServerClient*>& sockets, sf::TcpListener& listener);

	//void addToChatLog(std::string _in);
	//void alterChatLog(bool, std::string = "NULL");
	//void alterClientList(bool, Client*);

	void messageAllClients(std::string = "s");

	int prepareGame(ServerClient *);
	bool startGame(ServerClient*/*, Client**/);
	void setNickName(ServerClient *, sf::Packet _inPacket);
	void handelChat(sf::Packet _inPacket);
	void handelPing(Clock::time_point _RecevedTime);
	void handelRecevedBoard(sf::Packet _inPacket, ServerClient*);
	std::string handelShot(ServerClient * _inClient,sf::Packet _inPacket);
	void handelClientConnect(ServerClient* _inClient);

	void update();

	int genID();
	void printNumOfConnectedClients();
	int currentPing = 0;
	std::vector<ServerClient*> m_listOfClients;
	bool pingSent = false;

	void setTimeOut(int _in) { timeOut = _in; };
	int getTimeOut() { return timeOut; }

	ServerClient * m_AI;

protected:

	//std::vector<sf::TcpSocket*> m_sockets;
	//sf::SocketSelector  m_selector;
private:
	int timeOut=0;
	int timeOutlimit = 5;
	//std::vector<std::string> m_chatLog;

	ChatLog * m_chatLog;


	BattleShipsGame * m_Game = nullptr;

	ServerClient * m_PlayerOne = nullptr;
	ServerClient * m_PlayerTwo = nullptr;

	//sf::TcpListener m_listerner;
	sf::SocketSelector m_selector;
};