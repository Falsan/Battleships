#include "ChatServer.h"
#include "Server.h"
#include <chrono>
#include <iostream>
#include <thread>
#include <iomanip>      
#include "CellTypes.h"
//This line is 90 chars long ------------------------------------------------------------
ChatServer::ChatServer(std::vector<ServerClient*> _listOfClients,
	sf::SocketSelector& _selector)
{
	m_listOfClients = _listOfClients;
	m_selector = _selector;
	m_chatLog = new ChatLog;
}
ChatServer::~ChatServer()
{
	//if the game and AI have been initalized delete them
	delete m_chatLog;
	if (m_Game)
	{
		delete m_Game;
	}
	if (m_AI)
	{
		delete m_AI;
	}

	for (auto it = m_listOfClients.begin(); it != m_listOfClients.end(); it++)
	{
		(*it)->getPlayersBoard().clear();
		(*it)->getAIBoard().clear();
		delete (*it);
	}

}

void ChatServer::update()
{
	if (m_chatLog)
	{
		printNumOfConnectedClients();
		m_chatLog->printLog();
	}
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

void ChatServer::listen(sf::SocketSelector& selector, 
	std::vector<ServerClient*>& sockets, sf::TcpListener& listener)
{
	sf::Packet  inPacket;
	std::vector<Cell*> HoldBoard;
	//listen for conneections
	while (true)
	{
		//Has a communication come in?
		if (selector.wait(sf::milliseconds(500)))
		{
			//stores the time that the connection was receved
			auto RecevedTime = Clock::now();

			//is someone trying to connect?
			if (selector.isReady(listener))
			{
				ServerClient * m_client = new ServerClient();
				sf::TcpSocket* TCPSocket = new sf::TcpSocket;
				m_client->setSocket(TCPSocket);
				
				if (listener.accept(*m_client->getSocket()) != sf::Socket::Done)
				{
					//throw error
					m_chatLog->addToChatLog
						("Error, listener could not accept the client");
					
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

						
						if (socket->receive(inPacket) == sf::Socket::Disconnected);
						{

							int nothing = 0;

							//	removeClientWithSocket((*it)->getSocket());
							
						}
						

					
					//check to see if it's got something to say
					if (selector.isReady(*socket))
					{
						//Who is talking, and what do they want to say?
						int ID;
						int actionID;
						std::string confirm = "A";
						std::string chatLogText;
						sf::Packet HOLD;
						//If the user had disconnected
						
						socket->setBlocking(true);


						//The fist part of the message will always be the ID											
						inPacket >> ID;

						//finds the client that this is applicable to
						ServerClient * clientHOLD = findClientWithID(ID);
						//The second part of the message 
						//will always be the ID of what the user wants to say
						inPacket >> actionID;

						//swaps to the appropriate element based on in sent requet marker
						switch (actionID)
						{
							//shoot at board
						case ACTIONS::SHOOT:
							//If this player is currently in session
							if (clientHOLD->getGame())
							{
								std::string name;
								if (clientHOLD->getNickName() != "NULL")
								{
									name = clientHOLD->getNickName();
								}
								else
								{
									name = clientHOLD->getClientID();
								}
								name.append("takes a shot.");
								m_chatLog->addToChatLog(name);
								messageAllClients(handelShot(clientHOLD, inPacket));
							}
							break;
							//receve a board
						case ACTIONS::BOARD:
							chatLogText = " Receved board form ";
								
							m_chatLog->addToChatLog(chatLogText);
							handelRecevedBoard(inPacket, clientHOLD);
							messageAllClients();
							break;
							//Join a game 
						case ACTIONS::JOIN:
							if (prepareGame(clientHOLD) == 2)
							{
								chatLogText = "Player Joins a game.";
								m_chatLog->addToChatLog(chatLogText);

								//With two players ready the game starts
								startGame(m_PlayerOne/*, m_PlayerTwo*/);
							}
							messageAllClients();
							break;
							//Ping
						case ACTIONS::PING:
							//If we have clients that we are pinging
							if (currentPing < m_listOfClients.size())
							{
								handelPing(RecevedTime);
							}
							break;
						case ACTIONS::MESSAGE:
							handelChat(inPacket);
							break;
						case ACTIONS::NAME:
							setNickName(clientHOLD, inPacket);
							messageAllClients();
							break;
						}
					}
				}
			}
		}
		else
		{
			//Send a ping out to the current client
			if ((m_listOfClients.size() > 0) && (pingSent == false))
			{
				//current client has responded so is not timing out
				setTimeOut(0);
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
			}//This removes the client if they miss a set number of pings 
			//Deactivated due to disconnect issue but functional
			else if ((m_listOfClients.size() > 0) && (pingSent == true))
			{
				//If the client has not responed to the inital 
				//ping increase the time out values 
				setTimeOut(getTimeOut() +1);
				//if we have reached the limit of the time out values
				if (getTimeOut() >= timeOutlimit)
				{
					//alterClientList(0, m_listOfClients[currentPing]); 
				}
			}
		}
	}
}

//Hanels the incomming messages from the client requesting connection
void ChatServer::handelClientConnect(ServerClient* _inClient)
{
	//pullout the current number of connected users
	_inClient->setClientID(genID());

	//add client to sockets list
	m_listOfClients.push_back(_inClient);

	//add client to the selector
	m_selector.add(*_inClient->getSocket());
	m_chatLog->addToChatLog("Player has entered the room");
	//Inform the client of there server side ID
	sf::Packet p;
	p << _inClient->getClientID();

	_inClient->getSocket()->send(p);
}
//tests if any ships remain on a players board during each shot
//and return this to the client
int ChatServer::winTest()
{
	int AIcounter = 0;

	for (auto it = m_AI->getAIBoard().begin(); it != m_AI->getAIBoard().end(); it++)
	{
		if ((*it)->getType() == CellTypes::SHIP)
		{
			AIcounter++;
		}
	}

	if (AIcounter == 0)
	{
		return 1;
	}

	int playerCounter = 0;

	for (auto it = (m_AI->getOppenent())->getPlayersBoard().begin(); it !=
		(m_AI->getOppenent())->getPlayersBoard().end(); it++)
	{
		if ((*it)->getType() == CellTypes::SHIP)
		{
			playerCounter++;
		}
	}
	
	if (playerCounter == 0)
	{
		return 2;
	}

	return 0;
}

//due to client lockup a "procking" message was required to be sent to the
//currntly pinged client, this has now been copeted to retun a message to the
//one client
//also serves a mini output mannager
void ChatServer::messageAllClients(std::string _in)
{
	sf::Packet out;
	std::string output = _in;

	if (output == "ShotFalse")
	{
		std::string ident = "/";
		out << ident;
		out << m_AI->lastHit;
	}
	else
	{
		out << output;
	}

	for (auto it = m_listOfClients.begin(); it != m_listOfClients.end(); it++)
	{
		(*it)->getSocket()->send(out);
	}
}

//Once a game has started handels a player shootin at there oponents board
std::string ChatServer::handelShot(ServerClient * _inClient, sf::Packet _inPacket)
{
	int winCon;
	//passes there values to the current games update function
	if (_inClient->getGame()->update(_inPacket, _inClient))
	{
		// a possativly returned value
		//could be haneled by a number but the client requred it to be thus:
		return "ShotTrue";
	}
	else
	{
		//In the current set up a determined miss causes the the AI to begin its turn
		m_AI->AIShoot(m_AI->getOppenent());
		return "ShotFalse";
	}
	
	//The board is then tested for a win condition once the player or AI take a shot
	winCon = winTest();

	if (winCon == 1)
	{
		return "AIWin";
	}
	else if (winCon == 2)
	{
		return "PlayerWin";
	}
}

//Changes  a user to have a nick name of the users chousing
void ChatServer::setNickName(ServerClient* _inClient, sf::Packet _inPacket)
{
	std::string nickName;
	_inPacket >> nickName;

	std::string chat = "Player ";
	if (_inClient->getNickName() != "NULL")
	{
		chat.append(_inClient->getNickName());
	}
	chat.append("has set there name to: ");
	chat.append(nickName);

	m_chatLog->addToChatLog(chat);

	_inClient->setNickName(nickName);
}

//adds the chat to our local log and forwards the message to all other clients
void ChatServer::handelChat(sf::Packet _inPacket)
{
	sf::Packet outPacket;
	std::string chatMessage;
	std::string ident;
	ident = "£";
	//localy store the chat message 
	_inPacket >> chatMessage;

	m_chatLog->addToChatLog(chatMessage);

	outPacket << ident;
	outPacket << chatMessage;

	//run through all connected clients forwarding the adjusted packet
	for (auto it = m_listOfClients.begin(); it != m_listOfClients.end(); it++)
	{
		//Send the message out to all clients
		(*it)->getSocket()->send(outPacket);
	}
}

//handels how a compiled receved board will be directed
void ChatServer::handelRecevedBoard(sf::Packet _inPacket, ServerClient* _inClient)
{
	std::vector<int> inBoardlocs;
	int ignore;
	int HOLD;
	//remove the identity

	//Pulling the content out of the pair elements
	for (int it = 0; it < 15; it++)
	{
		_inPacket >> HOLD;
		inBoardlocs.push_back(HOLD);

		//pulling out the size element
		
	}

	_inClient->setUpBoard(inBoardlocs);
	_inClient->setBoardSet(true);

}

//handels an input of type Ping
void ChatServer::handelPing(Clock::time_point _RecevedTime)
{
	m_listOfClients[currentPing]->setLastPongVal(_RecevedTime);
	pingSent = false;
	currentPing++;
}

//The output and draw of the program called by the drawing thread and allowed to 
//loop in its own time
void ChatServer::printNumOfConnectedClients()
{
	//Slow but effecive
		system("CLS");
		std::cout << "Server is running" << std::endl <<
			"Room currently [" << m_listOfClients.size()
			<< "] connected clients" << std::endl;
		int numPrinted = 1;

		std::cout << "++++++ Currently running games ++++++" << std::endl;

		//once a game has begun prints out the current players, in this case the AI takes 
		//The role of player 2
		if (m_Game)
		{
			Draw::drawBoard(m_Game->getPlayerOne()->getPlayersBoard());
			Draw::drawBoard(m_AI->getAIBoard());
			std::cout << "Current game: BattleShips" << std::endl << "Current Players:"
				<< m_PlayerOne->getClientID() << " VS "
				<< /*m_PlayerTwo->getClientID()*/ "AI" << std::endl;
		}
		else
		{
			std::cout << "No games currently running" << std::endl;
		}

		//Showing all currently connected clients and there current pings
		std::cout << "++++++	Current client ping	 ++++++" << std::endl;
		//Only do this if someone is actaly in the room
		if (m_listOfClients.size() > 0)
		{
			for (auto it = m_listOfClients.begin(); it != m_listOfClients.end(); it++)
			{
				//Depending on wether or not the client has elected to give them
				//selves a nick name displays that name or the default ID
				if ((*it)->getNickName() == "NULL")
				{
					std::cout << (*it)->getClientID() << " > ";
				}
				else
				{
					std::cout << (*it)->getClientID() << (*it)->getNickName() << " > ";
				}

				(*it)->setDuration(std::chrono::duration_cast<std::chrono::milliseconds>
					(((*it)->getLastPing() - (*it)->getLastPong())).count());

				//Making the ping val readable
				std::cout << ((*it)->getDuration() / m_listOfClients.size())
					<< "ms" << std::endl;

				numPrinted++;
			}
		}
		else
		{
			std::cout << "No clients currently connected" << std::endl;
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

//searches our list for an ID and return that user for use
ServerClient * ChatServer::findClientWithID(int _ID)
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

//Create an ID for the new joining client based off of the highest prior AI
//for example 1,2,3,4 -> client 3 leaves -> 1,2,4 -> new client would receve a value of 5
int ChatServer::genID()
{
	//Create a generic ID for the user
	//loop through all of the users
	int currentHigh = 1;

	//In order to ensure that users are not give matching values
	//we always give them the highest
	for (auto it = m_listOfClients.begin(); it != m_listOfClients.end(); it++)
	{
		if ((*it)->getClientID()> currentHigh);
		{
			currentHigh = (*it)->getClientID() + 1;
		}
	}

	return currentHigh;
}

//when a player requests to join a game they are placed in to holding untill 
//an opponent is ready in the current state the player is automaticly placed verse an AI
int ChatServer::prepareGame(ServerClient * _player)
{
	//If playerOne is not a null pointer I.E. not currently containing a player
	if (!m_PlayerOne)
	{
		//asign the player to the slot
		m_PlayerOne = _player;
		//Normaly this would return a 1 signifying that a player is still required
		return 2;
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

//Create a new game with the players who are now ready,
//This would be were the two players are placed agnest on anther
//and allow for shooting and return to take place based on there
//turn order
bool ChatServer::startGame(ServerClient* _P1/*, Client* _P2*/)
{
	//Since this is based around The Ai, it not takes the place of the
	//the second palyer
	m_AI = new ServerClient();
	//takes one of our levels and loads it in 
	m_AI->AILoadLevel();
	//infoms the AI who there oponent is
	m_AI->setOponent(_P1);

	//ditto with the player
	_P1->setOponent(m_AI);

	//create a new game 
	m_Game = new BattleShipsGame(_P1,m_AI);

	//Inform the players that this is there game
	_P1->setGame(m_Game);

	//sets up the nodes required to run the AI
	_P1->setAINodes(1);

	return false;
}