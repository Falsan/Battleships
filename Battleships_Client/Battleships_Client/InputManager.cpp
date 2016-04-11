#include "InputManager.h"

std::string InputManager::pollInput(int &commandNumber)
{
	command = "none";
	while (command == "none")
	{
		//listen for input
		std::cin >> command;
		//if input, perform some sort of behaviour
		
		if (command[0] == '/')
		{
			if (command == "/say")
			{
				std::cout << "Please type your message:" << std::endl;
				std::cin >> command;
				commandNumber = 4;
				return command;
				//packetHandler->sendPacket(chatMessage, thisClient, selector, commandNumber, serverID);
			}
			else if (command == "/place")
			{
				std::cout << "Please select an X co-ordinate to place your ship at:" << std::endl;
				//std::cin >> coordinate;
				std::cout << "Please choose an orientation. 1 is up and 2 is across" << std::endl;
				//std::cin >> orientation;
				return command;
				//send the two ints off and tell the server to place the ship
			}
			else if (command == "/name")
			{
				std::cout << "Please enter a name";
				std::cin >> command;
				commandNumber = 6;
				return command;
			}
			else
			{
				std::cout << "Huh? Please enter a valid command." << std::endl;
				command = " ";
				return command;
			}
		}

	}

}