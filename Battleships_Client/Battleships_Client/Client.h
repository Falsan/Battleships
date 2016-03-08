#pragma once

#include <iostream>

#include "Game.h"

class Client
{
public:

	Client();
	~Client();

	Game* currentGame;
	
	void clientMenu();
	void connectToServer();
	void runClient();


protected:

private:

};