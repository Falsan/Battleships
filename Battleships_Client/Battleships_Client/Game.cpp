#include "Game.h"
#include "Helper.h"
#include <future>
//#include 



Game::Game(sf::TcpSocket& thisClient)
{

	//all initial creation for the game goes here
	userCommand = " ";
	commandNumber = NULL;
	windowLength = 800;
	windowWidth = 600;
	inputHandler = new InputManager;
	packetHandler = new PacketManager;
	phase = PLAYERIDENT;
	m_BoardManager = new BoardManager;
	m_chatLog = new ChatLog;
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
	delete m_BoardManager;
	delete m_chatLog;
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
	//if needed, pass the input to the packet manager to be sent to the server


	std::thread renderThread(&Game::render, this);
	std::thread inputThread(&Game::gameInputHandle, this);
	//inputThread.join();
	
	//update the game logic from the last server data
	//phase = packetHandler->recieveCurrentGameState(thisClient);
	while (true)
	{

		packetHandler->heartBeat(userCommand, thisClient, selector, commandNumber ,serverID, m_BoardManager);

		resolution(thisClient, selector);


	}
	//put that to the screen using the UI manager
	//clearScreen();
	//render();
	//request any input from the input manager
	//std::cout << "Connection stable";
	

	//listen for messages from the server
	//renderThread.join();
	//inputThread.join();
}

void Game::resolution(sf::TcpSocket& thisClient, sf::SocketSelector* selector)
{

	switch (phase)
	{
	case PhaseEnum::PLAYERIDENT:
		
		//ask the player their name
		m_chatLog->addToChatLog("Please input a name:");
		
		
		break;

	case PhaseEnum::WAIT:

		m_chatLog->addToChatLog("Please wait while we find you a game...");
		commandNumber = 3;
		userCommand = " ";
		break;

	case PhaseEnum::BOARDSETUP:

		//send the player input to the server
		m_chatLog->addToChatLog("Please place your ships:");
		
		break;


	case PhaseEnum::BOARDPLAY:
		
		m_chatLog->addToChatLog("Please select a position to fire");
		//send the player input to server

		//get the map to be displayed

		//ask the server if a win has been made

		//if there is a win, say that 
		break;

	case PhaseEnum::WIN:

		//if the server report was a win, then say win

		//if the server report was a lose, say lose

		//display the last map

		//send a quit command to the server after a minute
		break;

	default:
		m_chatLog->addToChatLog("Error");
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
	while (true)
	{
		userCommand = inputHandler->pollInput(commandNumber, m_BoardManager, m_chatLog);
	}
	
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