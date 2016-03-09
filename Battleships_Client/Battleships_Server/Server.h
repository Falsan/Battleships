#pragma once

#include <iostream>
#include <SFML\Network.hpp>

class Server
{
public:
	Server() {};
	~Server() {};
	const int SERVER_PORT = 53000;

	void runServer();
	void bindServerPort(sf::SocketSelector& selector, std::vector<sf::TcpSocket*>& sockets, sf::TcpListener& listener);
	void listen(sf::SocketSelector& selector, std::vector<sf::TcpSocket*>& sockets, sf::TcpListener& listener);

protected:

private:
	std::vector<sf::TcpSocket*> sockets;

	sf::SocketSelector selector;

	sf::TcpListener listener;


};