#pragma once

#include <iostream>
#include <SFML\Network.hpp>
#include <SFML\Audio.hpp>
#include <SFML\Graphics.hpp>
#include <SFML\Window.hpp>

#include "Game.h"
#include "AudioManager.h"

class Game;
class AudioManager;

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

	//std::ifstream m_dataFile;

	AudioManager* audioManager;

	bool serverConnected;

	std::string userCommand;

	ServerPort* clientServerPort;
	
	sf::TcpSocket socket;
	sf::SocketSelector* selector;
	
};