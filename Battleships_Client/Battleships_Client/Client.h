#pragma once

#include <iostream>
#include <SFML\Network.hpp>

#include "Game.h"

class Game;

struct ServerPort;

class Client
{
public:

	Client();
	~Client();

	Game* currentGame;
	
	void clientMenu();
	bool connectToServer();
	void runClient();

	enum ClientStates
	{
		CLIENT_NULLSTATE = 0,
		CLIENT_MENU,
		CLIENT_READY,
		CLIENT_PLAY_GAME,
		CLIENT_QUIT
	};

	int clientState;

protected:

private:

	bool serverConnected;

	std::string userCommand;

	ServerPort* clientServerPort;
	
	sf::TcpSocket socket;
	sf::SocketSelector* selector;
};