#include "InputManager.h"

std::string InputManager::pollInput()
{
	command = "none";
	while (command == "none")
	{
		//listen for input
		std::cin >> command;
		//if input, perform some sort of behaviour


		if (command[0] == '/')
		{
			//if it's valid, then set the command and pass it to the server via the packet manager
			
			return command;
		}
		else
		{
			command = "none";
			std::cout << "/n/nError: Command Input not recognised.";
			//if it isn't, set it so that the game loops back around
		}

	}

}