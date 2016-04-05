#include "GameManager.h"
#include "Listern.h"


GameManager::GameManager(gameData * _GD)
{
	m_inputManager = new inputHandeler(&getActionList(), &getClientList());

	std::thread Listern(&GameManager::listener, this);
	Listern.join();
}

GameManager::~GameManager()
{
	delete m_inputManager;
}

//thread for listerning out for a signal from the clients
bool GameManager::listener()
{
	m_listern = new Listener(getClientList(), getActionList(), getSelector());
	std::thread Draw(&GameManager::draw, this);
	m_listern->runServer();
	
	return true;
}

bool GameManager::draw()
{
	while (true)
	{
		m_listern->update();
	}
}

