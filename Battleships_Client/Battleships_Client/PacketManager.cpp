#include "PacketManager.h"

PacketManager::PacketManager()
{
	pong = "pong";
}

void PacketManager::sendPacket(std::string stringPacket, sf::TcpSocket& socket, sf::SocketSelector* selector, int commandNumber, int serverID)
{

	if (selector->wait(sf::milliseconds(10)) && selector->isReady(socket))
	{
		packetToSend << serverID;
		packetToSend << commandNumber;
		packetToSend << stringPacket;

		socket.send(packetToSend);
	}
}

std::string PacketManager::recievePacket(sf::TcpSocket& socket, sf::SocketSelector* selector, int serverID)
{

	while (true)
	{
		if (selector->wait(sf::milliseconds(10)) && selector->isReady(socket))
		{
			if (socket.receive(incomingPacket) == sf::Socket::Done)
			{
				incomingPacket >> incomingData;

				if (incomingData == "PING")
				{
					std::string s = "PONG";

					pongPacket << 1;
					pongPacket << s;
					socket.send(pongPacket);
				}
			}
		}

	}
	
	//std::cout << incomingData;

	return incomingData;
}

std::string PacketManager::recieveMapUpdate(sf::TcpSocket& socket)
{
	socket.receive(mapPacket);

	mapPacket << incomingMap;

	return incomingMap;
}

int PacketManager::recieveCurrentGameState(sf::TcpSocket& socket)
{
	socket.receive(gameStatePacket);

	gameStatePacket << gameState;

	return gameState;
}

int PacketManager::recieveServerID(sf::TcpSocket& socket, sf::SocketSelector* selector)
{
	sf::Packet serverIDPacket;
	int serverIDRecieved;
	if (selector->wait(sf::milliseconds(10)) && selector->isReady(socket))
	{
		if (socket.receive(serverIDPacket) == sf::Socket::Done)
		{
			serverIDPacket >> serverIDRecieved;
		}
	}



	//std::cout << incomingData;

	return serverIDRecieved;
}