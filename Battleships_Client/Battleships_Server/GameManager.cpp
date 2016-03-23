#include "GameManager.h"


gameManager::gameManager(gameData * _GD)
{
	//swap for smart pointer 
	std::unique_ptr<board> m_gameBoard;
	m_gameBoard.reset(new board(_GD));

	std::thread Listern(&gameManager::listern, this);
	std::thread Logic(&gameManager::logic, this);
	std::thread heartBeat(&gameManager::heartBeat, this);

}

//thread for listerning out for a signal from the clients
bool gameManager::listern()
{	
	while (true)
	{
		m_listern;

	}
	return true;
}

//thread for acting on signels from the clients
bool gameManager::logic()
{
	while (true)
	{


	}
	return true;
}

//thread for pinging with the clients
bool gameManager::heartBeat()
{
	while (true)
	{

	}
}