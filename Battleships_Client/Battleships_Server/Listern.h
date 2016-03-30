#pragma once

#include <iostream>
#include <SFML\Network.hpp>
#include <vector>
class listern
{
public:
	listern(std::vector<sf::TcpSocket*> * m_sockets, sf::SocketSelector * m_selector,sf::TcpListener * m_listener);
	~listern() = default;

	void update();

	const int SERVER_PORT = 53000;

	void runServer();
	void bindServerPort(sf::SocketSelector* selector, std::vector<sf::TcpSocket*>* sockets, sf::TcpListener* listener);
	void listen(sf::SocketSelector* selector, std::vector<sf::TcpSocket*>* sockets, sf::TcpListener* listener);

	std::vector<sf::TcpSocket*> * getSockets() { return m_sockets; };

protected:

private:
	std::vector<sf::TcpSocket*> * m_sockets;

	sf::SocketSelector * m_selector;

	sf::TcpListener * m_listener;
};