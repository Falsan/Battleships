#include "HeartBeat.h"
#include <thread>
#include <chrono>
#include <iostream>
using namespace std::literals;

heartBeatClass::heartBeatClass(std::vector<sf::TcpSocket*> * _clientVector)
{
	//auto start = std::chrono::high_resolution_clock::now();
	//auto end = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double, std::milli> elapsed = end - start;

	//m_clintVector = _clientVector;




}

heartBeatClass::~heartBeatClass()
{

}

void heartBeatClass::update(std::vector<sf::TcpSocket*> _clientVector)
{
	//for all the clients on our list 
	for (auto it = _clientVector.begin(); it != _clientVector.end(); it++)
	{

		//create and send a packet "PONG" 

		//Hold for return

		//if no return is found 

		//add one to the the time out counter


		//If this puts the client over 5 timeouts, set there connected to false

	}

	std::this_thread::sleep_for(5s);
}