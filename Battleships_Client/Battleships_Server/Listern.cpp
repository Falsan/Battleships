#include "Listern.h"
#include "Server.h"
#include <chrono>
#include <iostream>
#include <thread>


typedef std::chrono::high_resolution_clock Clock;


Listener::Listener(std::vector<Client*> _listOfClients, std::vector<inputAction*> _actionList, sf::SocketSelector& _selector)
{
	m_listOfClients = _listOfClients;
	m_actionList = _actionList;
	m_selector = _selector;
	
	//Launches a thread with the removal function
	std::thread Removal(&Listener::removeCompleatedTasks, this);
	std::thread Listerner(&Listener::runServer, this);
	Listerner.join();
	Removal.join();
}


void Listener::update()
{

	//printNumOfConnectedClients();

}

void Listener::runServer()
{
	sf::TcpListener m_listerner;
	bindServerPort(m_selector, m_listerner);

	listen(m_selector, m_listOfClients, m_listerner);
}

void Listener::bindServerPort(sf::SocketSelector& selector, sf::TcpListener& listerner)
{
	if (listerner.listen(SERVER_PORT) != sf::Socket::Done)
	{
		//error
		std::cout << "Error, couldn't find server";
	}

	selector.add(listerner);
}

void Listener::listen(sf::SocketSelector& selector, std::vector<Client*>& sockets, sf::TcpListener& listener)
{

	sf::TcpSocket * socket = new sf::TcpSocket;
	//listen for conneections
	while (true)
	{
		//Has a communication come in?
		if (selector.wait(sf::seconds(1)))
		{
			//If so->
			//is someone trying to connect?
			if (selector.isReady(listener))
			{
				if (listener.accept(*socket) != sf::Socket::Done)
				{
					//throw error
					std::cout << "Error, listener could not accept the client";
				}
				else
				{
					//Make a client object for the user to be housed in. 
					Client * m_client = new Client();

					//Create a generic ID for the user that connects
					//pullout the current number of connected users
					int IDHOLD = m_listOfClients.size()+1;
					
					//IDHOLDString.push_back(IDHOLD);

					m_client->setClientID(IDHOLD);

					//attach our socket to our client
					m_client->setSocket(socket);

					//add client to sockets list
					
					sockets.push_back(m_client);
		

					//add client to the selector
					selector.add(*socket);

					//Inform the client of there server side ID
					sf::Packet p;
					p << IDHOLD;

					m_client->getSocket()->send(p);
				}
			}//Otherwise what is the message being sent?
			else
			{
				//loop through each client in the sockets list

				for (auto& it = sockets.begin(); it != sockets.end(); it++)
				{
					//check to see if it's got something to say
					if (selector.isReady(*socket))
					{
						sf::Packet packet;
						socket->receive(packet);
						inputAction * HOLD = new inputAction();
						auto RecevedTime = Clock::now();
						
						int ID;
						std::string nickName;
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
							//setup
						case 4:
						
							break;
							//ping
						case 5:
						
							//marks down the exact time that the pong was receved 
							HOLD->setPongTime(std::chrono::high_resolution_clock::now());

							break;
							//NickName
						case 6:
							
							packet >> nickName;

							HOLD->setPlayerNickName(nickName);
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
		}
		else
		{
			//Send out ping to all connected clients
			for (auto& it = sockets.begin(); it != sockets.end(); it++)
			{
				auto sentTime = Clock::now();
				sf::Packet pingPack;
				std::string ping = "PING";
				pingPack << ping;

				(*it)->setLastPingVal(sentTime);
				(*it)->getSocket()->send(pingPack);

			}
			printNumOfConnectedClients();
			
		}
	}
}



void Listener::printNumOfConnectedClients()
{

		// V Remove for final V
		system("CLS");
		std::cout << "Server is running" << std::endl << "currently [" << m_listOfClients.size() << "] connected clients" << std::endl;
	

	for (auto it = m_listOfClients.begin(); it != m_listOfClients.end(); it++)
	{
		if((*it)->getNickName() == "NULL")
		{
			std::cout << (*it)->getClientID() << std::endl;
		}
		else
		{
			std::cout << (*it)->getNickName() << std::endl;
		}
		if (std::chrono::duration_cast<std::chrono::microseconds>((*it)->getLastPong() - (*it)->getLastPing()).count() > -100)
		{
			std::cout << std::chrono::duration_cast<std::chrono::microseconds>((*it)->getLastPong() - (*it)->getLastPing()).count() << std::endl;
		}
	}

}

//If the input handeler was able to compleate a task it will be marks so
//this function then removes the task from the task list
void Listener::removeCompleatedTasks()
{
	while (true)
	{
	//	for (auto it = m_actionList.begin(); it != m_actionList.end(); it++)
	//	{
		//	if ((*it)->getActionCompleate())
		//	{
				
				//m_actionList.erase(std::remove(m_actionList.begin(), m_actionList.end(), (*it)->getActionCompleate()), m_actionList.end());

		//	}
	//	}
	}
}