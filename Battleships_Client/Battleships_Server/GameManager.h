#ifndef _GAMEMANAGER_
#define _GAMEMANAGER_
#include <vector>
#include "Board.h"
#include "Cell.h"
#include <memory>
#include "GameData.h"
#include <thread>
#include "Listern.h"
#include "InputAction.h"

class gameManager {

public:
	gameManager(gameData * _GD);
	~gameManager() = default;

	listern * m_listern;
	
	bool listerner();

	bool logic();
	bool heartBeat();

	std::vector <inputAction*> m_actionList;

	board * getBoard() { return m_gameBoard; };
private:
	board * m_gameBoard;

	std::vector<sf::TcpSocket*> * m_sockets;

	sf::SocketSelector * m_selector;

	sf::TcpListener * m_listener;
};

#endif