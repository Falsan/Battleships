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



	board * getBoard() { return m_gameBoard; };

	std::vector<inputAction*> getActionList() { return m_actionList; };
	std::vector<sf::TcpSocket*> getClientList() { return m_clientList; };

	void setActionList(inputAction* _in) { m_actionList.push_back(_in); };
	void setClientList(sf::TcpSocket* _in) { m_clientList.push_back(_in); }

private:
	board * m_gameBoard;

	std::vector<inputAction*> m_actionList;
	std::vector<sf::TcpSocket*> m_clientList;

	std::vector<sf::TcpSocket*> * m_sockets;

	sf::SocketSelector * m_selector;

	sf::TcpListener * m_listener;
};

#endif