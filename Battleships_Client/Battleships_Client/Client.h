#pragma once

#include <iostream>
#include <SFML\Network.hpp>

#include "Game.h"

class Game;

class Client
{
public:

	Client() {};
	~Client() {};

	Game* currentGame;
	
	void clientMenu();
	bool connectToServer();
	void runClient();


protected:

private:

	bool serverConnected;
};