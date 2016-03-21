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

	void update();
	void render();
	void setup();
	void gameInputHandle();

protected:
	

private:

	std::string userCommand;

	InputManager* inputHandler;
	

};