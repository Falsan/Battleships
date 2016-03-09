#include "Server.h"

void Server::runServer()
{
	bindServerPort(selector, sockets, listener);

	listen(selector, sockets, listener);
}

void Server::bindServerPort(sf::SocketSelector& selector, std::vector<sf::TcpSocket*>& sockets, sf::TcpListener& listener)
{

	if (listener.listen(SERVER_PORT) != sf::Socket::Done)
	{
		//error
		std::cout << "Error, couldn't find server";
	}

	selector.add(listener);
}

void Server::listen(sf::SocketSelector& selector, std::vector<sf::TcpSocket*>& sockets, sf::TcpListener& listener)
{
	sf::TcpSocket* client = new sf::TcpSocket;
	//listen for conneections
	while (true)
	{
		//is there comms?
		if (selector.wait())
		{
			//is someone trying to connect?
			if (selector.isReady(listener))
			{

				if (listener.accept(*client) != sf::Socket::Done)
				{
					//throw error
					std::cout << "Error, listener could not accept the client";
				}
				else
				{
					//add client to sockets list
					sockets.push_back(client);
					//add client to the selector
					selector.add(*client);
				}
			}
			else
			{
				//loop through each client in the sockets list

				for (auto& iterator = sockets.begin(); iterator != sockets.end(); iterator++)
				{
					//check to see if it's got something to say
					if (selector.isReady(*client))
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

int main()
{
	return 0;
}