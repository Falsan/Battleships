#pragma once

#include "Client.h"
#include "InputManager.h"
#include "ServerPort.h"
#include "PacketManager.h"
#include "ChatLog.h"
#include <thread>
#include <SFML\Network.hpp>
#include "AudioManager.h"


class AudioManager;
class InputManager;
class PacketManager;

class Game
{
public:
	Game(sf::TcpSocket& thisClient);
	~Game();

	void update(sf::TcpSocket&, sf::SocketSelector*);
	//void render();
	void gameInputHandle();

protected:
	

private:

	BoardManager * m_BoardManager;
	BoardManager * AIBoard;
	ChatLog* m_chatLog;

	std::string userCommand;
	int coordinate;
	int orientation;
	std::string chatMessage;
	sf::TcpSocket currentClient;
	InputManager* inputHandler;
	PacketManager* packetHandler;
	//int phase;
	int serverID;
	
	std::string displayedMap;

	int commandNumber;
	//int windowLength;
	//int windowWidth;
	//std::string windowName;
	std::pair<int, int> shot;
	int winCon;
	//sf::RenderWindow* window;

	//sf::Font font;
	//sf::Text text;

	AudioManager* audioManager;
};