#include "Listern.h"
#include "Server.h"
#include <chrono>
#include <iostream>
#include <thread>
 
#include <iomanip>      

typedef std::chrono::high_resolution_clock Clock;


Listener::Listener(std::vector<Client*> _listOfClients, std::vector<inputAction*> _actionList, sf::SocketSelector& _selector)
{
	m_listOfClients = _listOfClients;
	m_actionList = _actionList;
	m_selector = _selector;


	//Launches a thread with the removal function
	std::thread Listerner(&Listener::runServer, this);
	Listerner.join();

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
	sf::Packet inPacket;
	sf::Packet outPacket;

	//listen for conneections
	while (true)
	{
		//Has a communication come in?
		if (selector.wait(sf::milliseconds(500)))
		{
			//If so->
			//is someone trying to connect?
			if (selector.isReady(listener))
			{	
				Client * m_client = new Client();
				sf::TcpSocket* TCPSocket = new sf::TcpSocket;
				m_client->setSocket(TCPSocket);


				if (listener.accept(*m_client->getSocket()) != sf::Socket::Done)
				{
					//throw error
					std::cout << "Error, listener could not accept the client";
				}
				else
				{
					//Make a client object for the user to be housed in. 
			
					
					//pullout the current number of connected users
					m_client->setClientID(genID());
		
					//attach our socket to our client


					//add client to sockets list
					sockets.push_back(m_client);
		
					//add client to the selector
					selector.add(*m_client->getSocket());

					//Inform the client of there server side ID
					sf::Packet p;
					p << m_client->getClientID();

					m_client->getSocket()->send(p);
				}





			}//Otherwise what is the message being sent?
			else
			{
				//loop through each client in the sockets list

				for (auto  it = sockets.begin(); it != sockets.end(); it++)
				{
					
					//check to see if it's got something to say
					if (selector.isReady(*(*it)->getSocket()))
					{
						int ID;
						std::string nickName;
						std::string chatMessage;
						int actionID;
						std::pair<int, int> pos;
						int menuOption;


						//If the user had disconnected
						if((*it)->getSocket()->receive(inPacket) == sf::Socket::Disconnected);
						{
							int nothing = 0;

						//	removeClientWithSocket((*it)->getSocket());
							(*it)->getSocket()->disconnect();
						}
						//inputAction * HOLD = new inputAction();
						auto RecevedTime = Clock::now();

						//Takes the sending players ID and adds it to the message object
						inPacket >> ID;

						//finds the client that this is applicable to
						Client * clientHOLD = findClientWithID(ID);				

						//takes the action distabution ID from the message and stores it
						inPacket >> actionID;

						//swaps to the appropriate element based on in sent requet marker
						switch (actionID)
						{
							//Send chat message
						case 0:

							//localy store the chat message 
							inPacket >> chatMessage;

							//run through all connected clients forwarding the packet
							for (auto it = m_listOfClients.begin(); it != m_listOfClients.end(); it++)
							{
								//Send the message out to all clients
								(*it)->getSocket()->send(inPacket);
							}
							break;

							//shoot at board
						case 1:
							//take out any board pos request
							inPacket >> pos.first;
							inPacket >> pos.second;			
							break;

							//join game
						case 2:
							inPacket >> menuOption;
							if (prepareGame(clientHOLD) == 2)
							{
								//With two players ready the game starts
								startGame(m_PlayerOne, m_PlayerTwo);
							}
							
							break;
							//client disconnect game 
						case 3:
							
							break;
							//Request current game Phase
						case 7:
							//If the current game has started
							if (m_Game)
							{
								//Send the current phase that the game is in
								outPacket << m_Game->getCurrentPhase();
								clientHOLD->getSocket()->send(outPacket);
							}
							break;
					
						case 5:

			
							break;
							//NickName
						case 6:
							
							inPacket >> nickName;

							clientHOLD->setNickName(nickName);
							break;
							//Ping
						case 4 :

							//marks down the exact time that the pong was receved 
							clientHOLD->setLastPongVal(RecevedTime);
							break;
						}
						//infroms the input handler that the action still needs to be carried out

					}
					
				}
			}
		}
		else
		{
			//Send out ping to all connected clients
			for (auto& it = sockets.begin(); it != sockets.end(); it++)
			{

				sf::Packet pingPack;
				std::string ping = "PING";
				pingPack << ping;

				auto sentTime = Clock::now();
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
		int numPrinted = 1;

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

		auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(( (*it)->getLastPing() - (*it)->getLastPong())).count();
			
		//Making the ping val readable
		std::cout << std::setprecision(0) <<(duration)/numPrinted << std::endl;
			
		numPrinted++;
	}

}



//serches and removes the passed client
void Listener::removeClientWithSocket(sf::TcpSocket* _id)
{
	int loopVal = m_listOfClients.size();
	for (int i = 0; i < loopVal; i++)
	{
		if (loopVal > 0)
		{
			if (m_listOfClients[i]->getSocket() == _id)
			{
				m_listOfClients.erase(m_listOfClients.begin() + i);
				loopVal= loopVal - 1;
			}
		}
	}
}

Client * Listener::findClientWithID(int _ID)
{
	for (auto it = m_listOfClients.begin(); it != m_listOfClients.end(); it++)
	{
		if ((*it)->getClientID() == _ID)
		{
			return (*it);
		}
	}
	return nullptr;
}


int Listener::genID()
{
	//Create a generic ID for the user
	//loop through all of the users
	int currentHigh=1; 
		
	//In order to ensure that users are not give matching values we always give them the highest
	for (auto it = m_listOfClients.begin(); it != m_listOfClients.end(); it++)
	{
		if((*it)->getClientID()> currentHigh);
		{
			currentHigh = (*it)->getClientID()+1;
		}
	}
	
	return currentHigh;
}

int Listener::prepareGame(Client * _player)
{
	//If playerOne is not a null pointer I.E. not currently containing a player
	if (!m_PlayerOne)
	{
		//asign the player to the slot
		m_PlayerOne = _player;
		return 1;
	}
	//Otherwise test if player two is avalable
	else if (!m_PlayerTwo)
	{
		m_PlayerTwo = _player;
		return 2;
	}
	//Otherwise return false
	return 0;
}

//Create a new game with the players who are now ready
bool Listener::startGame(Client* _P1, Client* _P2)
{
	//create a new game 
	m_Game = new BattleShipsGame(_P1, _P2);
	//Inform the players that this is there game
	_P1->setGame(m_Game);
	_P2->setGame(m_Game);

	//place the game on a new thread
	//std::thread(&m_Game, BattleShipsGame(_P1, _P2));


	return false;
}