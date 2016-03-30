#pragma once

#include <iostream>
#include <SFML\Network.hpp>
#include <vector>
#include "Client.h"
#include "InputAction.h"
class listern
{
public:
	listern(std::vector<sf::TcpSocket*> _listOfClients, std::vector<inputAction*> m_actionList);
	~listern() = default;

	void update();

	const int SERVER_PORT = 53000;

	void runServer();
	void bindServerPort(sf::SocketSelector& selector, sf::TcpListener& listerner);
	void listen(sf::SocketSelector& selector, std::vector<sf::TcpSocket*>& sockets, sf::TcpListener& listener);

	//std::vector<sf::TcpSocket*>  getSockets() { return m_sockets; };

	std::vector<sf::TcpSocket*> m_listOfClients;

	std::vector<inputAction*> m_actionList;

protected:

	std::vector<sf::TcpSocket*> m_sockets;
	//sf::SocketSelector  m_selector;
private:




	//sf::TcpListener * m_listener;
};