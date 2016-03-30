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
	std::vector<Client*> getClientList() { return m_clientList; };
	sf::SocketSelector * getSelector() { return m_selector; }

	void setActionList(inputAction* _in) { m_actionList.push_back(_in); };
	void setClientList(Client* _in) { m_clientList.push_back(_in); }
	void setSelector(sf::SocketSelector* _in) { m_selector = _in; }

private:
	board * m_gameBoard;

	std::vector<inputAction*> m_actionList;
	std::vector<Client*> m_clientList;

	std::vector<sf::TcpSocket*> * m_sockets;

	sf::SocketSelector * m_selector;

	sf::TcpListener * m_listener;

	sf::SocketSelector* m_selector;
};

#endif