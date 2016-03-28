#pragma once
#include <iostream>
#include <SFML\Network.hpp>
#include <vector>



class heartBeat
{
public:
	heartBeat(std::vector<sf::TcpSocket*> * _clintVector);
	~heartBeat();

	void update(std::vector<sf::TcpSocket*>  _clintVector);


	std::vector<sf::TcpSocket*> * m_clintVector;

};