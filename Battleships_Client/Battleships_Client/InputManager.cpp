#include "InputManager.h"

void InputManager::pollInput()
{
	std::string command = "none";
	while (command == "none")
	{
		//listen for input
		std::cin >> command;
		//if input, perform some sort of behaviour


	//if (command == )
	//{
		//if it's valid, then set the command
	//}
	//else
	//{
	//	command = "none";
		//std::cout << "Error: Command Input not recognised.";
		//if it isn't, set it so that the game loops back around
	//}
	}
}