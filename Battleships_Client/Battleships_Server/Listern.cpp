#include "Listern.h"
#include "Server.h"

#include <iostream>

const int SERVER_PORT(53000);


listern::listern(std::vector<sf::TcpSocket*> * _sockets, sf::SocketSelector * _selector, sf::TcpListener * _listener)
{
	m_sockets = _sockets;
	m_selector = _selector;
	m_listener = _listener;

}


void listern::update()
{

}

void listern::runServer()
{
	bindServerPort(m_selector, m_sockets, m_listener);

	listen(m_selector, m_sockets, m_listener);
}

void listern::bindServerPort(sf::SocketSelector * selector, std::vector<sf::TcpSocket*>* sockets, sf::TcpListener* listener)
{

	if (listener->listen(SERVER_PORT) != sf::Socket::Done)
	{
		//error
		std::cout << "Error, couldn't find server";
	}

	selector->add(*listener);
}

void listern::listen(sf::SocketSelector* selector, std::vector<sf::TcpSocket*>* sockets, sf::TcpListener* listener)
{
	sf::TcpSocket* client = new sf::TcpSocket;
	//listen for conneections
	while (true)
	{
		//is there comms?
		if (selector->wait())
		{
			//is someone trying to connect?
			if (selector->isReady(*listener))
			{

				if (listener->accept(*client) != sf::Socket::Done)
				{
					//throw error
					std::cout << "Error, listener could not accept the client";
				}
				else
				{
					//add client to sockets list
					sockets->push_back(client);
					//add client to the selector
					selector->add(*client);
				}
			}
			else
			{
				//loop through each client in the sockets list

				for (auto& iterator = sockets->begin(); iterator != sockets->end(); iterator++)
				{
					//check to see if it's got something to say
					if (selector->isReady(*client))
					{
						sf::Packet packet;
						std::string s;

						//store packet as string
						packet >> s;

						//send packet to connected clients
						client->send(packet);

						//recieve packet
						client->receive(packet);

						//this is where we will check to make sure there are connections

						packet >> s;

						std::cout << s;

					}
					else
					{

					}
				}
			}
		}
	}
}