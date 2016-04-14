#include "Game.h"
#include "Helper.h"
#include <future>
//#include 



Game::Game(sf::TcpSocket& thisClient)
{

	//all initial creation for the game goes here
	userCommand = " ";
	commandNumber = NULL;
	//windowLength = 800;
	//windowWidth = 600;
	inputHandler = new InputManager;
	packetHandler = new PacketManager;
	//phase = PLAYERIDENT;
	m_BoardManager = new BoardManager;
	AIBoard = new BoardManager;
	m_chatLog = new ChatLog;
	audioManager = new AudioManager;
	audioManager->loadSoundFromFile();
	audioManager->loadSound();
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
	delete audioManager;
	delete inputHandler;
	delete packetHandler;
	delete m_BoardManager;
	delete m_chatLog;
	delete AIBoard;
	//delete window;
	//all deletion goes here
}


void Game::update(sf::TcpSocket& thisClient, sf::SocketSelector* selector)
{
	//if needed, pass the input to the packet manager to be sent to the server

	winCon = 0;

	//audioManager->connectionSound->play();
	//audioManager->music->play();
	m_chatLog->addToChatLog("Arg! Welcome to battleships! Type /help for help.");
	m_chatLog->printLog();
	//std::thread renderThread(&Game::render, this);
	std::thread inputThread(&Game::gameInputHandle, this);
	
	while (winCon == 0)
	{

		packetHandler->heartBeat(userCommand, thisClient, selector, commandNumber ,serverID, m_BoardManager, AIBoard, shot, winCon);

		//render();

		/*if (userCommand != " ")
		{
			audioManager->chatPingSound->play();
		}
		else if (userCommand == "/name")
		{
			audioManager->chatPingSound->play();
		}*/
		if (userCommand == "Shoot")
		{
			audioManager->shotSound->play();
		}


	}
	
}

void Game::gameInputHandle()
{
	while (true)
	{
		userCommand = inputHandler->pollInput(commandNumber, m_BoardManager, AIBoard, m_chatLog, shot);
		m_chatLog->addToChatLog("Sent!");
		m_chatLog->printLog();
	}
	
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