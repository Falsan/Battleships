#include "PacketManager.h"

void PacketManager::sendPacket(std::string stringPacket)
{
	sf::Packet packet;

	packet >> stringPacket;

	//socket.send(packet);
}