#include "Game.h"
#include "Helper.h"
#include <future>


Game::Game(sf::TcpSocket& thisClient)
{
	//all initial creation for the game goes here
	windowLength = 800;
	windowWidth = 600;
	inputHandler = new InputManager;
	packetHandler = new PacketManager;
	phase = PLAYERIDENT;
//	window = new sf::RenderWindow(sf::VideoMode(windowLength, windowWidth), windowName);
	
//	font.loadFromFile("arial.ttf");
	//text.setFont(font);
	//text.setString("HelloWorld");
	//text.setCharacterSize(24);
	//text.setColor(sf::Color::Red);
	//text.setStyle(sf::Text::Regular);
	
}

Game::~Game()
{
	delete inputHandler;
	delete packetHandler;
	//delete window;
	//all deletion goes here
}

void Game::setup(sf::TcpSocket& thisClient)
{
	//threads launch here
	//sf::RenderWindow window(sf::VideoMode(800, 600), "Battleships");
	//any leftover variables are set up
	
	//begins update loop
}

void Game::update(sf::TcpSocket& thisClient, sf::SocketSelector* selector)
{
	std::thread renderThread(&Game::render, this);
	packetHandler->heartBeat(thisClient, selector, serverID);
	
	//std::thread serverThread(&Game::gamePacketHandle, &thisClient);
	
	//update the game logic from the last server data
	//phase = packetHandler->recieveCurrentGameState(thisClient);
	//resolution(thisClient, selector);

	//put that to the screen using the UI manager
	clearScreen();
	//render();
	//request any input from the input manager
	std::cout << "Connection stable";
	

	//if needed, pass the input to the packet manager to be sent to the server

	//if (userCommand[0] == '/')
	//{
	//	packetHandler->sendPacket(userCommand, thisClient);
	//}

	//displayedMap = packetHandler->recieveMapUpdate(thisClient);

	//listen for messages from the server

}

void Game::resolution(sf::TcpSocket& thisClient, sf::SocketSelector* selector)
{

	switch (phase)
	{
	case PhaseEnum::PLAYERIDENT:
		
		//ask the player their name
		std::cout << "Please input a user name:" << std::endl;
		std::cin >> userCommand;
		//recieve server ID
		serverID = packetHandler->recieveServerID(thisClient, selector);

		commandNumber = 6;

		//send name to server
		packetHandler->sendPacket(userCommand, thisClient, selector, commandNumber, serverID);

	
		//std::cout << serverID;

	case PhaseEnum::BOARDSETUP:

		//send the player input to the server

		//get the map to be displayed

		//check to see if done

		//if done, send a command to the server saying so

	case PhaseEnum::BOARDPLAY:

		//send the player input to server

		//get the map to be displayed

		//ask the server if a win has been made

		//if there is a win, say that 

	case PhaseEnum::WIN:

		//if the server report was a win, then say win

		//if the server report was a lose, say lose

		//display the last map

		//send a quit command to the server after a minute

	default:
		std::cout << "Error";
		break;
	}
}

void Game::render()
{
	//render everything to screen
	// run the program as long as the window is open
	//while (window->isOpen())
	//{
	//	// check all the window's events that were triggered since the last iteration of the loop
	//	sf::Event event;
	//	while (window->pollEvent(event))
	//	{
	//		// "close requested" event: we close the window
	//		if (event.type == sf::Event::Closed)
	//		{
	//			window->close();
	//		}
	//	}

	//	// clear the window with black color
	//	window->clear(sf::Color::Black);

	//	// draw everything here...
	//	// window.draw(...);
	//	//window->draw(text);

	//	// end the current frame
	//	window->display();
	//}
	//std::cout << displayedMap << std::endl;
}

void Game::gameInputHandle()
{
	userCommand = inputHandler->pollInput();
}

void Game::gamePacketHandle(sf::TcpSocket& thisClient)
{
	//auto map = std::async(std::launch::async, &PacketManager::recieveMapUpdate);

	//displayedMap = packetHandler->recieveMapUpdate(thisClient);
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