#pragma once

#include "Client.h"
#include "InputManager.h"
#include "ServerPort.h"
#include <thread>
#include <SFML\Network.hpp>

class InputManager;

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

	std::string userCommand;

	InputManager* inputHandler;
	

};