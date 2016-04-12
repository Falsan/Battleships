#include "InputManager.h"
#include "LoadIn.h"

std::string InputManager::pollInput(int &commandNumber, BoardManager * _BoardManager, ChatLog* _Chatlog, std::pair<int, int> &shot)
{
	std::string command = "none";
	while (command == "none")
	{
		//listen for input
		std::cin >> command;
		//if input, perform some sort of behaviour
		
		if (command[0] == '/')
		{
			if (command == "/say")
			{
				_Chatlog->addToChatLog("Please type your message:");
				std::cin >> command;
				commandNumber = 5;
				return command;
				//packetHandler->sendPacket(chatMessage, thisClient, selector, commandNumber, serverID);
			}
			else if (command == "/place")
			{
				_BoardManager->startUp();
				commandNumber = 2;
				return _BoardManager->boardToSend(_BoardManager->getBoardObject()->getBoard());
				
				
				/*std::string orientation;
				std::string position;
				std::cout << "Please select an X co-ordinate to place your ship at:" << std::endl;
				std::cin >> position;
				std::cout << "Please choose an orientation. 1 is up and 2 is across" << std::endl;
				std::cin >> orientation;

				command = position + orientation;
				commandNumber = 45;
				return command;*/
				//send the two ints off and tell the server to place the ship
			}
			else if (command == "/name")
			{
				_Chatlog->addToChatLog("Please enter a name");
				std::cin >> command;
				commandNumber = 6;
				return command;
			}
			else if (command == "/shoot")
			{
				_Chatlog->addToChatLog("Please enter an X and Y co-ordinate to shoot at");
				shot = playerShot();
				commandNumber = 1;
				command = "Shoot";
				return command;
			}
			else if (command == "/join")
			{
				_Chatlog->addToChatLog("Please wait while we connect to the game");
				commandNumber = 3;
				command = "Join";
				return command;
			}
			else if (command == "/save")
			{
				std::string fileName;
				_Chatlog->addToChatLog("Please input a name for the file");
				std::cin >> fileName;
				LoadIn::saveFile(_BoardManager->getBoardObject()->getBoard(), fileName);
				//_BoardManager->getBoard() = LoadIn::loadFile(fileName, m_board->getBoard());
				commandNumber = 4;
				command = " ";
				return command;
			}
			else
			{
				_Chatlog->addToChatLog("Huh? Please enter a valid command.");
				command = " ";
				return command;
			}
		}

	}

}

std::pair<int, int> InputManager::playerShot()
{
	int x;
	int y;
	std::cin >> x;
	std::cin >> y;

	std::pair<int, int> shotCoord;

	shotCoord.first = x;
	shotCoord.second = y;

	return shotCoord;
}