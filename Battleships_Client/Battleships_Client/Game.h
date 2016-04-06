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
	Game(sf::TcpSocket& thisClient);
	~Game();

	void update(sf::TcpSocket&, sf::SocketSelector*);
	void render();
	void setup(sf::TcpSocket&);
	void gameInputHandle();
	void gamePacketHandle(sf::TcpSocket&);
	void resolution(sf::TcpSocket& thisClient, sf::SocketSelector* selector);

protected:
	

private:

	std::string userCommand;
	sf::TcpSocket currentClient;
	InputManager* inputHandler;
	PacketManager* packetHandler;
	int phase;
	int serverID;
	
	std::string displayedMap;

	enum PhaseEnum
	{
		BOARDSETUP = 0,
		BOARDPLAY = 1,
		WIN = 2,
		PLAYERIDENT = 3
	};

	int commandNumber;
	int windowLength;
	int windowWidth;
	std::string windowName;
	sf::RenderWindow* window;
};