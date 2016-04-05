#include "InputHandeler.h"



inputHandeler::inputHandeler(std::vector<inputAction*>*_actionList, std::vector<Client*> * _clientList)
{
	m_actionList = _actionList;
	m_clientList = _clientList;
}


bool inputHandeler::handelInputs()
{
	sf::Packet message;
	while (true)
	{
		//If something is on our action list 
		if (m_actionList->size() > 0)
		{//runthrough the list compleating the actions
			for (auto it = m_actionList->begin(); it != m_actionList->end(); it++)
			{
				Client * clientWithID = findClientWithID((*it)->getPlayerID());
				switch ((*it)->getActionID())
				{
					//Send chat message
				case 0:
					
					//Drop the message in to the packet 
					message << (*it)->getMessage();

					for (auto itt = m_clientList->begin(); itt != m_clientList->end(); itt++)
					{
						//Send the message out to all clients
						(*itt)->getSocket()->send(message);
					}

					//Mark that the message has been handeled by the input manager
					(*it)->setActionCompleate(true);
					break;
					//shoot at board
				case 1:


					//take out any board pos request
					break;
					//menu option
				case 2:
					break;
					//client disconnect game 
				case 3:		

					break;
					//setup
				case 4:
					break;
					//ping
				case 5:
					clientWithID->setLastPongVal((*it)->getPongTime());

					break;
					//NickName
				case 6:
					clientWithID->setNickName((*it)->getPlayerNick());
					break;
				}
			}
		}
	}
	return false;
}

Client * inputHandeler::findClientWithID(int _in)
{
	for (auto it = m_clientList->begin(); it != m_clientList->end(); it++)
	{
		if ((*it)->getClientID() == _in)
		{
			return (*it);
		}
	}
	return nullptr;
}