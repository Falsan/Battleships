#include "PacketManager.h"

PacketManager::PacketManager()
{
	//pong = "pong";
}

void PacketManager::sendPacket(std::string stringPacket, sf::TcpSocket& socket, sf::SocketSelector* selector, int commandNumber, int serverID)
{

	if (selector->wait(sf::milliseconds(10)) && selector->isReady(socket))
	{
		//packetToSend << serverID;
		//packetToSend << commandNumber;
		//packetToSend << stringPacket;

		//socket.send(packetToSend);
	}
}

//PUT SERVER ID IN HERE 
std::string PacketManager::recievePacket(sf::TcpSocket& socket, sf::SocketSelector* selector, int serverID)
{
	
	if (selector->wait(sf::milliseconds(10)) && selector->isReady(socket))
	{
		if (socket.receive(incomingPacket) == sf::Socket::Done)
		{
			incomingPacket >> incomingData;

			if (incomingData == "PING")
			{
				std::string s = "PONG";

				//pongPacket << serverID;
				//pongPacket << s;
				//socket.send(pongPacket);
				return NULL;
			}
		}
	}
	//std::cout << incomingData;

	return incomingData;
}


int PacketManager::recieveServerID(sf::TcpSocket& socket, sf::SocketSelector* selector)
{
	sf::Packet serverIDPacket;
	int serverIDRecieved =0;
//	while (!selector->isReady(socket)) {}
	
		if (socket.receive(serverIDPacket) == sf::Socket::Done)
		{
			serverIDPacket >> serverIDRecieved;
		}
	



	//std::cout << incomingData;

	return serverIDRecieved;
}


void PacketManager::heartBeat(std::string & userInput, sf::TcpSocket& socket, sf::SocketSelector* selector, int &commandNumber, int &serverID, BoardManager * _BoardManager, BoardManager * _AIBoard , std::pair<int, int> shot)
{
	sf::Packet outgoingPacket;
	

	while (serverID == 0)
	{
		serverID = recieveServerID(socket, selector);
	}
	//while (true)
	//{

		if (selector->wait(sf::milliseconds(10)) && selector->isReady(socket))
		{
			if (socket.receive(incomingPacket) == sf::Socket::Done)
			{
				incomingPacket >> incomingData;

				if (incomingData == "ShotTrue")
				{
					std::cout << "Hit, please shoot again" << std::endl;
					_AIBoard->getBoardObject()->getCell(shot.first, shot.second)->setType(CellTypes::HIT);
					Draw::drawBoard(_BoardManager->getBoardObject()->getBoard());
					Draw::drawBoard(_AIBoard->getBoardObject()->getBoard());
				}
				else if (incomingData == "ShotFalse")
				{
					std::cout << "Miss, the ai will now shoot" << std::endl;
					Draw::drawBoard(_BoardManager->getBoardObject()->getBoard());
					Draw::drawBoard(_AIBoard->getBoardObject()->getBoard());
				}
				else if (incomingData[0] == '/')
				{
					//char HOLDXC;
					//char HOLDYC;
					int HOLD;
					int HOLD2;
					int HOLD1;
					incomingPacket >> HOLD;
					HOLD1 = HOLD / 10;
					HOLD2 = (HOLD1 * 10) - HOLD;

					HOLD2 = abs(HOLD2);

				
					if (_BoardManager->getBoardObject()->getCell(HOLD1, HOLD2)->getType() == CellTypes::SHIP)
					{
						_BoardManager->getBoardObject()->getCell(HOLD1, HOLD2)->setType(CellTypes::HIT);
					}
					else
					{
						_BoardManager->getBoardObject()->getCell(HOLD1, HOLD2)->setType(CellTypes::MISS);
					}
					Draw::drawBoard(_BoardManager->getBoardObject()->getBoard());
					Draw::drawBoard(_AIBoard->getBoardObject()->getBoard());
					
				}

					outgoingData = userInput;



					if (outgoingData == " ")
					{
						std::string s = "PONG";

						commandNumber = 4;

						outgoingPacket << serverID;
						outgoingPacket << commandNumber;
						outgoingPacket << s;
						socket.send(outgoingPacket);
					}
					else if (outgoingData == "BoardCompiled")
					{
						outgoingPacket << serverID;
						outgoingPacket << commandNumber;
						
						
						for (int it = 0; it < _BoardManager->m_compiledBoard.size(); it++)
						{
							
							outgoingPacket << _BoardManager->m_compiledBoard[it];
						}

						socket.send(outgoingPacket);

					}
					else if(outgoingData == "Shoot")
					{
						_AIBoard->getBoardObject()->getCell(shot.first, shot.second)->setType(CellTypes::MISS);

						outgoingPacket << serverID;
						outgoingPacket << commandNumber;
						outgoingPacket << shot.first;
						outgoingPacket << shot.second;
						outgoingData = " ";
						socket.send(outgoingPacket);
					}
					else
					{
						outgoingPacket << serverID;
						outgoingPacket << commandNumber;
						outgoingPacket << outgoingData;
						socket.send(outgoingPacket);
						outgoingData = " ";
						commandNumber = 4;
					}
		
					userInput = " ";
			}
		}
	//}
		
}











////PUT SERVER ID IN HERE 
//std::string PacketManager::recievePacket(sf::TcpSocket& socket, sf::SocketSelector* selector, int serverID)
//{
//
//
//	serverID = recieveServerID(socket, selector);
//
//	while (true)
//	{
//		if (selector->wait(sf::milliseconds(10)) && selector->isReady(socket))
//		{
//			if (socket.receive(incomingPacket) == sf::Socket::Done)
//			{
//				incomingPacket >> incomingData;
//
//				pongPacket.clear();
//
//				if (incomingData == "PING")
//				{
//					std::string s = "PONG";
//
//					pongPacket << serverID;
//					pongPacket << s;
//					socket.send(pongPacket);
//				}
//				else if (incomingData == "/CHAT")
//				{
//					int i = 3;
//					std::string s = "I HAVE RECEVED A MESSAGE";
//
//					pongPacket << serverID;
//					pongPacket << i;
//					pongPacket << s;
//					socket.send(pongPacket);
//				}
//				else if (incomingData == "I HAVE RECEVED A MESSAGE")
//				{
//					std::cout << incomingData;
//				}
//			}
//		}
//	}
//
//	//std::cout << incomingData;
//
//	return incomingData;
//}
//

