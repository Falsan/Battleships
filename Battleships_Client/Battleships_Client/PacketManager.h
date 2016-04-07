#pragma once

#include "Client.h"

class PacketManager
{
public:
	PacketManager();
	~PacketManager() {};

	void sendPacket(std::string stringPacket, sf::TcpSocket& socket, sf::SocketSelector* selector, int, int);

	std::string recievePacket(sf::TcpSocket& socket, sf::SocketSelector* selector, int serverID=0);
	std::string recieveMapUpdate(sf::TcpSocket& socket);
	int recieveCurrentGameState(sf::TcpSocket& socket);
	int recieveServerID(sf::TcpSocket& socket, sf::SocketSelector* selector);
	void heartBeat(sf::TcpSocket& socket, sf::SocketSelector* selector, int serverID);



protected:

private:
	sf::Packet packetToSend;
	sf::Packet incomingPacket;
	sf::Packet pongPacket;
	sf::Packet mapPacket;
	sf::Packet gameStatePacket;
	int gameState;
	std::string incomingMap;
	std::string incomingData;
	std::string pong;

};

