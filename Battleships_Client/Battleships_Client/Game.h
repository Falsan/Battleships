#pragma once

#include "Client.h"
#include "InputManager.h"
#include "ServerPort.h"
#include "PacketManager.h"
#include <thread>
#include <SFML\Network.hpp>

class InputManager;
class PacketManager;

class Game
{
public:
	Game();
	~Game();

	void update(sf::TcpSocket&);
	void render();
	void setup(sf::TcpSocket&);
	void gameInputHandle();
	void gamePacketHandle(sf::TcpSocket&);

protected:
	

private:

	std::string userCommand;
	sf::TcpSocket currentClient;
	InputManager* inputHandler;
	PacketManager* packetHandler;
	
	std::string displayedMap;
};