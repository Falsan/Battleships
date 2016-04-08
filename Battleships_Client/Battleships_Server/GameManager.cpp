#include "GameManager.h"
#include "ChatServer.h"


GameManager::GameManager()
{

	listener();
	//std::thread Listern(&GameManager::listener, this);

	std::thread Server(&ChatServer::runServer, m_listern);
	std::thread Draw(&GameManager::draw, this);

	while (true)
	{

	}

	
}

GameManager::~GameManager()
{

}

//thread for listerning out for a signal from the clients
bool GameManager::listener()
{	
	m_listern = new ChatServer(getClientList(), getSelector());
	m_listOfChatRooms.push_back(m_listern);

	return true;
}

void GameManager::draw()
{
	while (true)
	{
		if (m_listOfChatRooms.size() > 0)
		{
			int roomCount = 1;
			for (auto it = m_listOfChatRooms.begin(); it != m_listOfChatRooms.end(); it++)
			{
				std::cout << "Room " << roomCount << ":" << std::endl;
				(*it)->update();
			}
		}
	}
}

