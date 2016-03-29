#include "Listern.h"
#include "Server.h"

#include <iostream>



listern::listern(std::vector<Client* > _listOfClients, std::vector<inputAction*> _actionList)
{
	//m_listOfClients = _listOfClients;
	m_actionList = _actionList;
}


void listern::update()
{

}

void listern::runServer()
{
	std::vector<sf::TcpSocket*> m_sockets;
	sf::TcpListener m_listerner;
	sf::SocketSelector m_selector;

	bindServerPort(m_selector, m_listerner);

	listen(m_selector, m_sockets, m_listerner);
}

void listern::bindServerPort(sf::SocketSelector& selector, sf::TcpListener& listerner)
{	
	if (listerner.listen(SERVER_PORT) != sf::Socket::Done)
	{
		//error
		std::cout << "Error, couldn't find server";
	}

	selector.add(listerner);
}

void listern::listen(sf::SocketSelector& selector, std::vector<sf::TcpSocket*>& sockets, sf::TcpListener& listener)
{
	sf::TcpSocket* client = new sf::TcpSocket;
	//listen for conneections
	while (true)
	{
		//is there comms?
		if (selector.wait())
		//{
			//is someone trying to connect?
			if (selector.isReady(listener))
			{

				if (listener.accept(*client) != sf::Socket::Done)
				{
					//throw error
					std::cout << "Error, listener could not accept the client";
				}
				else
				{
					//add client to sockets list
					sockets.push_back(client);
					//add client to the selector
					selector.add(*client);
				}
			}
			else
			{
				//loop through each client in the sockets list

				for (auto& iterator = sockets.begin(); iterator != sockets.end(); iterator++)
				{
					//check to see if it's got something to say
					if (selector.isReady(*client))
					{
						inputAction * HOLD = new inputAction();

						sf::Packet packet;
						std::string ID;
						std::string chatMessage;
						int actionID;
						int posOne;
						int posTwo;
						int menuOption;

						//Takes the sending players ID and adds it to the message object
						packet >> ID;
						HOLD->setPlayerID(ID);

						//takes the action distabution ID from the message and stores it
						packet >> actionID;
						HOLD->setActionID(actionID);

						//swaps to the appropriate element based on in sent requet marker
						switch (actionID)
						{
							//Send chat message
						case 0:
							packet >> chatMessage;
							HOLD->setMessage(chatMessage);
							break;
							
							//shoot at board
						case 1:
							//take out any board pos request
							packet >> posOne;
							packet >> posTwo;
							HOLD->setPos(posOne, posTwo);
							break;
							//menu option
						case 2:
							packet >> menuOption;

							HOLD->setMenuAction(menuOption);
							break;
							//client disconnect game 
						case 3:
							
							break;
						}
						//infroms the input handler that the action still needs to be carried out
						HOLD->setActionCompleate(false);

						//V may need a mutex and function here V
						m_actionList.push_back(HOLD);

						//send packet to connected clients
						//client->send(packet);

						//recieve packet
						//client->receive(packet);

						//this is where messages will be passed to the message hadler


					}
				}
			}
		//}
	}
}