#pragma once

#include "Client.h"

class PacketManager
{
public:
	PacketManager() {};
	~PacketManager() {};

	void sendPacket(std::string stringPacket, sf::TcpSocket socket);
	void sendPacket(int integerPacket);

	void recievePacket(sf::TcpSocket socket);

protected:

private:
};

