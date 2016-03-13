#pragma once

#include "Client.h"
#include "InputManager.h"
#include "ServerPort.h"
#include <thread>
#include <SFML\Network.hpp>

class Game
{
public:
	Game();
	~Game();

	void update();
	void render();
	void setup();

protected:
	

private:

	InputManager* inputHandler;
	ServerPort* clientServerPort;

	sf::TcpSocket socket;
	sf::SocketSelector selector;

};