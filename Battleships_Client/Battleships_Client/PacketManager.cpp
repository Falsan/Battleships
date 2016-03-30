#include "PacketManager.h"

PacketManager::PacketManager()
{
	pong = "pong";
}

void PacketManager::sendPacket(std::string stringPacket, sf::TcpSocket& socket)
{
	packetToSend >> stringPacket;

	socket.send(packetToSend);
}

std::string PacketManager::recievePacket(sf::TcpSocket& socket)
{
	socket.receive(incomingPacket);

	incomingPacket << incomingData;

	if (incomingData == "ping")
	{
		pongPacket >> pong;
		socket.send(pongPacket);
	}

	return incomingData;
}

std::string PacketManager::recieveMapUpdate(sf::TcpSocket& socket)
{

	socket.receive(mapPacket);

	mapPacket << incomingMap;

	return incomingMap;
}