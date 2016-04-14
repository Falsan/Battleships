#include "GameManager.h"
#include "ChatServer.h"
#include <chrono>
#include <thread>

//managing the creation of threads for rooms 

using namespace std::chrono_literals;
GameManager::GameManager()
{

	listener();

	std::thread Server(&ChatServer::runServer, m_listern);
	std::thread Draw(&GameManager::draw, this);
	//additional rooms can be added here 

	//any future updates that require continual feeback may be placed here
	//else replaced with a .join
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

//Continual drawing function that will draw indipendent of what else is going on 
void GameManager::draw()
{
	while (true)
	{
		if (m_listOfChatRooms.size() > 0)
		{
			int roomCount = 1;
			for (auto it = m_listOfChatRooms.begin();
			it != m_listOfChatRooms.end(); it++)
			{
				(*it)->update();
			}
		}
		std::this_thread::sleep_for(1s);
	}
}

