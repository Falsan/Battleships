#include "GameManager.h"
#include "Listern.h"
#include "HeartBeat.h"

gameManager::gameManager(gameData * _GD)
{
	//swap for smart pointer 
	//std::unique_ptr<board> m_gameBoard;
	//m_gameBoard.reset(new board(_GD));

	 m_selector = new sf::SocketSelector;

	//liseten out for new clients and add them to our client list
	std::thread Listern(&gameManager::listerner, this);
	//test the current clients to make sure they are still connected 
	//std::thread heartBeat(&gameManager::heartBeat, this);

	//carry out the comunicated actions 
	//logic();
	while (true)
	{
		// V Remove for final V
		system("CLS");
		std::cout << "Server is running" << std::endl << "currently [" << m_clientList.size() << "] connected clients" << std::endl;
	}


}

//thread for listerning out for a signal from the clients
bool gameManager::listerner()
{
	m_listern = new listern(getClientList(), getActionList());

	m_listern->runServer();
	return true;
}

//thread for acting on signels from the clients
bool gameManager::logic()
{
	if (getActionList().size() > 0)
	{
		//if our list of actions is not empty carry out all the actions on our list;
		//This list is read only 
		for (auto it = getActionList().begin(); it != getActionList().end(); it++)
		{
			//If the current action has not been compleated 
			if (!(*it)->getActionCompleate())
			{
				switch ((*it)->getActionID())
				{
					//Send chat message
				case 0:
					break;
					//shoot at board
				case 1:
					break;
					//menu option
				case 2:
					break;
					//client disconnect game 
				case 3:
					break;
				}
			}
		}
	}


	return true;
}

//thread for pinging with the clients
bool gameManager::heartBeat()
{
	heartBeatClass * m_heartBeat = new heartBeatClass(m_sockets);
	while (true)
	{

	}
}