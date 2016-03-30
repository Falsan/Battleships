#pragma once

#include "Client.h"

class PacketManager
{
public:
	PacketManager();
	~PacketManager() {};

	void sendPacket(std::string stringPacket, sf::TcpSocket& socket);

	std::string recievePacket(sf::TcpSocket& socket);
	std::string recieveMapUpdate(sf::TcpSocket& socket);

protected:

private:
	sf::Packet packetToSend;
	sf::Packet incomingPacket;
	sf::Packet pongPacket;
	sf::Packet mapPacket;
	std::string incomingMap;
	std::string incomingData;
	std::string pong;

};

