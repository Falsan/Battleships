#include "Game.h"

Game::Game()
{
	//all initial creation for the game goes here
	inputHandler = new InputManager;
	clientServerPort = new ServerPort;
}

Game::~Game()
{
	delete inputHandler;
	delete clientServerPort;
	//all deletion goes here
}

void Game::setup()
{
	//threads launch here

	//any leftover variables are set up

	//begins update loop

	socket.setBlocking(false);

	sf::Socket::Status status = socket.connect("127.0.0.1", clientServerPort->SERVER_PORT);

	selector.add(socket);

	if (status != sf::Socket::Done)
	{
		std::cout << "Error, could not connect to server";
	}
}

bool Game::update()
{
	//std::thread inputThread(inputHandler->pollInput);
	//update the game logic from the last server data

	//put that to the screen using the UI manager

	//request any input from the input manager
	std::cout << "Loop test";
	//if needed, pass the input to the packet manager to be sent to the server
	//inputThread.join();
	return true;
}

void Game::render()
{
	//use the ui manager to render everything to screen
}

/*socket.setBlocking(false);

	sf::Socket::Status status = socket.connect("127.0.0.1", SERVER_PORT);
	if (status != sf::Socket::Done)
	{
		std::cout << "Error, could not connect to server";
	}

	selector.add(socket);

	//a thread is required to constantly poll for data
	auto handle = std::async(std::launch::async, []
	{
		while (true)
		{
			sf::Packet packet;
			if (selector.wait(sf::milliseconds(500)) &&
				selector.isReady(socket))
			{
				if (socket.receive(packet) == sf::Socket::Done)
				{
					std::string s;
					//take the contents of the packet
					packet << s;
					//convert into a string
					std::cout << s;
				}
			}
		}
	});

	while (true)
	{
		std::string m;
		sf::Packet message;
		//poll for input
		std::cin >> m;

		//once received, create a packet and send it
		message >> m;
		socket.send(message);
	}*/