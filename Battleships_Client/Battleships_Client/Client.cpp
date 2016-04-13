#include "Client.h"
#include "Helper.h"


Client::Client()
{
	selector = new sf::SocketSelector;
	audioManager = new AudioManager;
	clientServerPort = new ServerPort;
	//m_BoardManager = new BoardManager;
}

Client::~Client()
{
	delete selector;
	delete audioManager;
	//delete m_BoardManager;
}

void Client::runClient()
{
	clientState = CLIENT_MENU;
	audioManager->loadSoundFromFile();
	audioManager->loadSound();
	//start the main game loop

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

			if (connectToServer() == false)//if they can't connect, say so and return to menu
			{
				clientState = CLIENT_MENU;
			}
			else	//if they can connect to the server, make a new instance of the game and call the 'play game' function
			{
				audioManager->connectionSound->play();
				clientState = CLIENT_PLAY_GAME;
				currentGame = new Game(socket);
				currentGame->setup(socket);

				
				currentGame->update(socket, selector);
				
				delete currentGame;	//once the game is done, delete that new instance

				clientState = CLIENT_MENU;
			}



		}
		
		//if they choose to quit then exit the loop
	}
	delete clientServerPort;
}

bool Client::connectToServer()
{
	//ask the server if it is up
	socket.setBlocking(true);
	sf::TcpSocket::Status status = socket.connect("127.0.0.1", 53000/*clientServerPort->SERVER_PORT*/);
	if (status != sf::TcpSocket::Done)
	{
		//if the server takes too long, it must be down, so return a string which says so
		std::cout << "Error, could not connect to server" << std::endl;
		return false;
	}
	//if it's up, then try to connect to a listener
	selector->add(socket);
	
	return true;
}

void Client::clientMenu()
{
	//ask if the player wants to input something
	std::cout << "Please input a command" << std::endl;

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
	//Client* newClient = new Client;
	std::unique_ptr<Client> newClient(new Client);

	newClient->runClient();

	//delete newClient

	return 0;
}