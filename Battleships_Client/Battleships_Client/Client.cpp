#include "Client.h"

void Client::runClient()
{
	//start the main game loop

	//go to the menu and ask the user for input

	//if they choose to play a new game, connect to the server

	//if they can connect to the server, make a new instance of the game and call the 'play game' function

	//once the game is done, delete that new instance

	//if they can't connect, say so and return to menu

	//if they choose to quit then exit the loop
}

void Client::connectToServer()
{
	//ask the server if it is up

	//if it's up, then try to connect to a listener

	//wait for a little bit

	//if the server takes too long, it must be down, so return a string which says so
}

void Client::clientMenu()
{
	//ask if the player wants to input something

	//if they do, check the input

	//change the state to the appropriate input
}

int main()
{
	Client* newClient = new Client;

	newClient->runClient();

	delete newClient;

	return 0;
}