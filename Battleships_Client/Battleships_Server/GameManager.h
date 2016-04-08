#ifndef _GAMEMANAGER_
#define _GAMEMANAGER_
#include <vector>
#include "Board.h"
#include "Cell.h"
#include <memory>

#include <thread>
#include "ChatServer.h"


class GameManager {

public:
	GameManager();
	~GameManager();

	ChatServer * m_listern;
	bool listener();
	void draw();
	std::vector<Client*> getClientList() { return m_clientList; };
	sf::SocketSelector getSelector() { return m_selector; }
	void setClientList(Client* _in) { m_clientList.push_back(_in); }
	void setSelector(sf::SocketSelector _in) { m_selector = _in; }

	std::vector<ChatServer*> m_listOfChatRooms;

private:

	std::vector<Client*> m_clientList;
	std::vector<sf::TcpSocket*> * m_sockets;
	sf::SocketSelector m_selector;
	sf::TcpListener * m_listener;
};

#endif