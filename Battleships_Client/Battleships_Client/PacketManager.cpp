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


void PacketManager::heartBeat(std::string userInput, sf::TcpSocket& socket, sf::SocketSelector* selector, int commandNumber, int serverID)
{

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

				if (incomingData == "PING")
				{
					if (outgoingData == "")
					{
						std::string s = "PONG";

						outgoingPacket << serverID;
						outgoingPacket << commandNumber;
						outgoingPacket << s;
						socket.send(outgoingPacket);
					}
					else
					{
						outgoingPacket << serverID;
						outgoingPacket << commandNumber;
						outgoingPacket << outgoingData;
						socket.send(outgoingPacket);
					}
				}
				//else //else the server is clearly sending a command and that command should be dealt with
				//{

				//}
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

