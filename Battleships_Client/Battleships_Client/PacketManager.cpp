#include "PacketManager.h"

void PacketManager::sendPacket(std::string stringPacket, sf::TcpSocket& socket)
{
	sf::Packet packet;

	packet >> stringPacket;

	socket.send(packet);
}

std::string PacketManager::recievePacket(sf::TcpSocket& socket)
{
	sf::Packet incomingPacket;

	std::string incomingData;

	socket.receive(incomingPacket);

	incomingPacket << incomingData;

	return incomingData;
}

std::string PacketManager::recieveMapUpdate(sf::TcpSocket& socket)
{
	sf::Packet mapPacket;

	std::string incomingMap;

	socket.receive(mapPacket);

	mapPacket << incomingMap;

	return incomingMap;
}