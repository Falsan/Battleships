#pragma once
#include <iostream>
#include <SFML\Network.hpp>
#include <vector>



class heartBeatClass
{
public:
	heartBeatClass(std::vector<sf::TcpSocket*> * _clintVector);
	~heartBeatClass();

	void update(std::vector<sf::TcpSocket*>  _clintVector);


	std::vector<sf::TcpSocket*> * m_clintVector;

};