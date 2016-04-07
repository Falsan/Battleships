#pragma once

#include <iostream>
#include <SFML\Network.hpp>
#include <vector>
#include "Client.h"
#include "InputAction.h"
#include "Game.h"
#include <memory>
class Listener
{
public:
	Listener(std::vector<Client*> _listOfClients, std::vector<inputAction*> m_actionList, sf::SocketSelector& _selector);
	~Listener() = default;

	void update();

	const int SERVER_PORT = 53000;

	void removeClientWithSocket(sf::TcpSocket* _id);
	Client * findClientWithID(int _ID);

	void runServer();
	void bindServerPort(sf::SocketSelector& selector, sf::TcpListener& listerner);
	void listen(sf::SocketSelector& selector, std::vector<Client*>& sockets, sf::TcpListener& listener);
	int prepareGame(Client *);
	bool startGame(Client*, Client*);

	int genID();

	void printNumOfConnectedClients();

	//std::vector<sf::TcpSocket*>  getSockets() { return m_sockets; };

	int currentPing = 0;

	std::vector<Client*> m_listOfClients;

	bool pingSent = false;

	std::vector<inputAction*> m_actionList;

protected:

	//std::vector<sf::TcpSocket*> m_sockets;
	//sf::SocketSelector  m_selector;
private:


	BattleShipsGame * m_Game;

	Client * m_PlayerOne = nullptr;
	Client * m_PlayerTwo = nullptr;

	//sf::TcpListener m_listerner;
	sf::SocketSelector m_selector;
};