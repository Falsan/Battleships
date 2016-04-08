#include "ChatServer.h"
#include "Server.h"
#include <chrono>
#include <iostream>
#include <thread>
#include "BoardManager.h"
#include <mutex>
#include <iomanip>      

void ChatServer::addToChatLog(std::string _in)
{ 
	alterChatLog(true, _in);
}

void ChatServer::alterChatLog(bool _in,std::string _inString)
{
	std::mutex mtx;

	mtx.lock();
	if (_in)
	{
		//drops the first item on the the vector list of our chat log
		m_chatLog.push_back(_inString);

		//If we have reached capacity on our chat log removes the first elemnt 
		if (m_chatLog.size() > 10)
		{
			m_chatLog.erase(m_chatLog.begin());
		}
	}
	else
	{
		for (auto it = m_chatLog.begin(); it != m_chatLog.end(); it++)
		{
			std::cout << (*it) << std::endl;
		}
	}

	mtx.unlock();


}

ChatServer::ChatServer(std::vector<Client*> _listOfClients, sf::SocketSelector& _selector)
{
	m_listOfClients = _listOfClients;
	m_selector = _selector;
	
	//Launches a thread with the removal function
	//runServer();


}

void ChatServer::update()
{

		printNumOfConnectedClients();
		alterChatLog(false);


}


void ChatServer::runServer()
{
	sf::TcpListener m_listerner;
	bindServerPort(m_selector, m_listerner);

	listen(m_selector, m_listOfClients, m_listerner);
}

void ChatServer::bindServerPort(sf::SocketSelector& selector, sf::TcpListener& listerner)
{
	if (listerner.listen(SERVER_PORT) != sf::Socket::Done)
	{
		//error
		std::cout << "Error, couldn't find server";
	}

	selector.add(listerner);
}

void ChatServer::listen(sf::SocketSelector& selector, std::vector<Client*>& sockets, sf::TcpListener& listener)
{
	sf::Packet inPacket;
	
	//listen for conneections
	while (true)
	{
		//Has a communication come in?
		if (selector.wait(sf::milliseconds(50)))
		{
			//stores the time that the connection was receved
			auto RecevedTime = Clock::now();

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
					//delete the created client setup since it is no longer needed
					delete m_client;
				}
				else
				{
					handelClientConnect(m_client);
				}

			}//Otherwise what is the message being sent?
			else
			{
				//loop through each client in the sockets list

				for (auto it = sockets.begin(); it != sockets.end(); it++)
				{
					auto socket = (*it)->getSocket();
					
					//check to see if it's got something to say
					if (selector.isReady(*socket))
					{
						//Who is talking, and what do they want to say?
						int ID;
						int actionID;
								
						//If the user had disconnected

						socket->setBlocking(true);
						if (socket->receive(inPacket) == sf::Socket::Disconnected);
						{
							int nothing = 0;

							//	removeClientWithSocket((*it)->getSocket());
							//(*it)->getSocket()->disconnect();
						}

						//The fist part of the message will always be the ID											
						inPacket >> ID;

						//finds the client that this is applicable to
						Client * clientHOLD = findClientWithID(ID);

						//The second part of the message will always be the ID of what the user wants to say
						inPacket >> actionID;

						//swaps to the appropriate element based on in sent requet marker
						switch (actionID)
						{
							//shoot at board
						case 1:
							//If this platyer is currently in session
							if (clientHOLD->getGame())
							{
								handelShot(clientHOLD, inPacket);
							}
							break;
							//receve a board
						case 2:
							if (m_Game)
							{
								handelRecevedBoard(inPacket, clientHOLD);
							}
							break;
							//Join a game 
						case 3:
							if (prepareGame(clientHOLD) == 2)
							{
								//With two players ready the game starts
								startGame(m_PlayerOne, m_PlayerTwo);
							}
							break;
							//Ping
						case 4:
							//If we have clients that we are pinging
							if (currentPing < m_listOfClients.size())
							{
								handelPing(RecevedTime);
							}
							break;
						case 5:
							handelChat(inPacket);
							break;
						case 6:
							setNickName(clientHOLD,inPacket);
							break;
						case 7:
							//If the current game has started
							if (clientHOLD->getGame())
							{
								//Send the current phase that the game is in
							//	outPacket << m_Game->getCurrentPhase();
							//	clientHOLD->getSocket()->send(outPacket);
							}
							break;

						}
						//infroms the input handler that the action still needs to be carried out
					}
				}
			}
		}
		else
		{
			if ((m_listOfClients.size() > 0) && (pingSent == false))
			{
				//If we have run through all the clients 
				if (currentPing >= m_listOfClients.size())
				{
					currentPing = 0;
				}
				sf::Packet pingPack;
				std::string ping = "PING";
				pingPack << ping;

				auto sentTime = Clock::now();
				m_listOfClients[currentPing]->setLastPingVal(sentTime);
				m_listOfClients[currentPing]->getSocket()->send(pingPack);

				pingSent = true;
			}
		}
	}
}

void ChatServer::handelClientConnect(Client* _inClient)
{
	//pullout the current number of connected users
	_inClient->setClientID(genID());

	//add client to sockets list
	m_listOfClients.push_back(_inClient);

	//add client to the selector
	m_selector.add(*_inClient->getSocket());

	//Inform the client of there server side ID
	sf::Packet p;
	p << _inClient->getClientID();

	_inClient->getSocket()->send(p);
}


void ChatServer::handelShot(Client * _inClient, sf::Packet _inPacket)
{
	std::pair<int, int> pos;
	//take out any board pos request
	_inPacket >> pos.first;
	_inPacket >> pos.second;


	_inClient->getOppenent()->getPlayersBoard();





}


void ChatServer::setNickName(Client * _inClient, sf::Packet _inPacket)
{
	std::string nickName;
	_inPacket >> nickName;
	_inClient->setNickName(nickName);
}

void ChatServer::handelChat(sf::Packet _inPacket)
{
	sf::Packet outPacket;
	std::string chatMessage;
	//localy store the chat message 
	_inPacket >> chatMessage;
	std::cout << chatMessage << std::endl;
	outPacket << chatMessage;

	//run through all connected clients forwarding the adjusted packet
	for (auto it = m_listOfClients.begin(); it != m_listOfClients.end(); it++)
	{
		//Send the message out to all clients
		(*it)->getSocket()->send(outPacket);
	}
}

void ChatServer::handelRecevedBoard(sf::Packet _inPacket,Client* _inClient)
{
	std::vector < std::pair<int, int> >inBoardlocs;
	int ignore;
	//Pulling the content out of the pair elements
	for (auto it = inBoardlocs.begin(); it != inBoardlocs.end(); it++)
	{
		_inPacket >> (*it).first;
		_inPacket >> (*it).second;

		//pulling out the size element
		_inPacket >> ignore;
	}

	_inClient->setUpBoard(inBoardlocs);
	_inClient->setBoardSet(true);

}


void ChatServer::handelPing(Clock::time_point _RecevedTime)
{
	m_listOfClients[currentPing]->setLastPongVal(_RecevedTime);
	pingSent = false;
	currentPing++;
}

void ChatServer::printNumOfConnectedClients()
{


		// V Remove for final V
		system("CLS");
		std::cout << "Server is running" << std::endl << "currently [" << m_listOfClients.size() << "] connected clients" << std::endl;
		int numPrinted = 1;

		if (m_Game)
		{
			std::cout << "Current game: BattleShips" << std::endl << "Current Players:" << m_PlayerOne->getClientID() << " VS " << m_PlayerTwo->getClientID() << std::endl;
		}

		for (auto it = m_listOfClients.begin(); it != m_listOfClients.end(); it++)
		{
			if ((*it)->getNickName() == "NULL")
			{
				std::cout << (*it)->getClientID() << std::endl;
			}
			else
			{
				std::cout << (*it)->getNickName() << std::endl;
			}

			if (std::chrono::duration_cast<std::chrono::milliseconds>(((*it)->getLastPing() - (*it)->getLastPong())).count() > 0)
			{
				(*it)->setDuration(std::chrono::duration_cast<std::chrono::milliseconds>(((*it)->getLastPing() - (*it)->getLastPong())).count());
			}
			//Making the ping val readable
			std::cout << ((*it)->getDuration() / m_listOfClients.size()) << "ms" << std::endl;

			numPrinted++;
		}
	
}

//serches and removes the passed client
void ChatServer::removeClientWithSocket(sf::TcpSocket* _id)
{
	int loopVal = m_listOfClients.size();
	for (int i = 0; i < loopVal; i++)
	{
		if (loopVal > 0)
		{
			if (m_listOfClients[i]->getSocket() == _id)
			{
				m_listOfClients.erase(m_listOfClients.begin() + i);
				loopVal = loopVal - 1;
			}
		}
	}
}

Client * ChatServer::findClientWithID(int _ID)
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


int ChatServer::genID()
{
	//Create a generic ID for the user
	//loop through all of the users
	int currentHigh = 1;

	//In order to ensure that users are not give matching values we always give them the highest
	for (auto it = m_listOfClients.begin(); it != m_listOfClients.end(); it++)
	{
		if ((*it)->getClientID()> currentHigh);
		{
			currentHigh = (*it)->getClientID() + 1;
		}
	}

	return currentHigh;
}

int ChatServer::prepareGame(Client * _player)
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
		//ensure that the same player has not entered the game twice
		if (m_PlayerOne == m_PlayerTwo)
		{
			m_PlayerTwo = nullptr;
			return 1;
		}

		return 2;
	}
	//Otherwise return false
	return 0;
}

//Create a new game with the players who are now ready
bool ChatServer::startGame(Client* _P1, Client* _P2)
{
	//create a new game 
	m_Game = new BattleShipsGame(_P1, _P2);
	//Inform the players that this is there game
	_P1->setGame(m_Game);
	_P2->setGame(m_Game);

	_P1->setOponent(_P2);
	_P2->setOponent(_P1);

	//place the game on a new thread
	//std::thread(&m_Game, BattleShipsGame(_P1, _P2));


	return false;
}