#include "HeartBeat.h"
#include <thread>
#include <chrono>
#include <iostream>
	using namespace std::literals;

heartBeat::heartBeat(std::vector<sf::TcpSocket*> * _clientVector)
{
	//auto start = std::chrono::high_resolution_clock::now();
	//auto end = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double, std::milli> elapsed = end - start;

	//m_clintVector = _clientVector;



	
}

heartBeat::~heartBeat()
{

}

void heartBeat::update(std::vector<sf::TcpSocket*> _clientVector)
{
	//for all the clients on our list 
	for (auto it = _clientVector.begin(); it != _clientVector.end(); it++)
	{
		



	}

	std::this_thread::sleep_for(5s);
}