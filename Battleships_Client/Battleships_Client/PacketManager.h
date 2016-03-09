#pragma once

#include "Client.h"

class PacketManager
{
public:
	PacketManager() {};
	~PacketManager() {};

	void sendPacket(std::string stringPacket);
	void sendPacket(int integerPacket);

	void recievePacket();

protected:

private:
};

