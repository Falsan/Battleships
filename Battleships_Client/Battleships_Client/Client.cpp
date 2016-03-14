#include "Client.h"

void Client::runClient()
{
	clientState = CLIENT_MENU;
	//start the main game loop
	clientServerPort = new ServerPort;
	while (clientState != CLIENT_QUIT)
	{
		//go to the menu and ask the user for input
		if (clientState == CLIENT_MENU)
		{
			clientMenu();
		}
		//if they choose to play a new game, connect to the server
		if (clientState == CLIENT_READY)
		{
			connectToServer();
		}
		
		if (connectToServer() == false)//if they can't connect, say so and return to menu

		{
			std::cout << "Error, cannot connect to server";
			clientState == CLIENT_MENU;
		}
		else	//if they can connect to the server, make a new instance of the game and call the 'play game' function
		{
			clientState == CLIENT_PLAY_GAME;
			currentGame = new Game;
			currentGame->setup();

			while (currentGame->update() == true)
			{
				currentGame->update();
				currentGame->render();
			}
			delete currentGame;	//once the game is done, delete that new instance
		}

		//if they choose to quit then exit the loop
	}
	delete clientServerPort;
}

bool Client::connectToServer()
{
	//ask the server if it is up
	
	socket.setBlocking(false);

	sf::Socket::Status status = socket.connect("127.0.0.1", clientServerPort->SERVER_PORT);

	//if it's up, then try to connect to a listener
	selector.add(socket);

	//wait for a little bit
	if (status != sf::Socket::Done)
	{
		std::cout << "Error, could not connect to server";
		return false;
	}
	//if the server takes too long, it must be down, so return a string which says so
	return true;
}

void Client::clientMenu()
{
	//ask if the player wants to input something
	std::cout << "Please input a command";

	//if they do, check the input
	std::cin >> userCommand;

	//change the state to the appropriate input
	if (userCommand == "play")
	{
		clientState = CLIENT_READY;
	}
	else if (userCommand == "quit")
	{
		clientState = CLIENT_QUIT;
	}
	else
	{
		clientState = CLIENT_MENU;
		std::cout << "Invalid Command";
	}
}

int main()
{
	Client* newClient = new Client;

	newClient->runClient();

	delete newClient;

	return 0;
}