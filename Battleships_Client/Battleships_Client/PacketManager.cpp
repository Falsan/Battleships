#include "PacketManager.h"

void PacketManager::sendPacket(std::string stringPacket, sf::TcpSocket socket)
{
	sf::Packet packet;

	packet >> stringPacket;

	socket.send(packet);
}

void PacketManager::recievePacket(sf::TcpSocket socket)
{
	sf::Packet incomingPacket;

	std::string incomingData;

	socket.receive(incomingPacket);

	incomingPacket << incomingData;
}