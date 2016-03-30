#pragma once
#include <iostream>
#include <SFML\Network.hpp>
#include <vector>
#include "Client.h"


class heartBeatClass
{
public:
	heartBeatClass(std::vector<sf::TcpSocket*> * _clintVector, sf::SocketSelector& _selector);
	~heartBeatClass();

	void update(std::vector<Client*>  _clintVector);


	std::vector<sf::TcpSocket*> * m_clintVector;
	
	sf::TcpListener m_listerner;
	sf::SocketSelector m_selector;
};