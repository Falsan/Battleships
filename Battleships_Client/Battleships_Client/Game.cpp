#include "Game.h"

Game::Game()
{
	//all initial creation for the game goes here
	inputHandler = new InputManager;
	packetHandler = new PacketManager;
}

Game::~Game()
{
	delete inputHandler;
	delete packetHandler;
	//all deletion goes here
}

void Game::setup(sf::TcpSocket& thisClient)
{
	//threads launch here

	//any leftover variables are set up
	thisClient;
	//begins update loop
}

void Game::update(sf::TcpSocket& thisClient)
{
	std::thread inputThread(&Game::gameInputHandle, this);
	//std::thread serverThread(&Game::gamePacketHandle, this);
	//update the game logic from the last server data

	//put that to the screen using the UI manager

	//request any input from the input manager
	std::cout << "Loop test";
	//if needed, pass the input to the packet manager to be sent to the server

	//listen for messages from the server

	inputThread.join();
	//serverThread.join();
	render();
}

void Game::render()
{
	//render everything to screen
	std::cout << displayedMap << std::endl;
}

void Game::gameInputHandle()
{
	inputHandler->pollInput();
}

void Game::gamePacketHandle(sf::TcpSocket& thisClient)
{
	displayedMap = packetHandler->recieveMapUpdate(thisClient);
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