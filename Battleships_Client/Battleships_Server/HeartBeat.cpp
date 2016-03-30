#include "HeartBeat.h"
#include <thread>
#include <chrono>
#include <iostream>
using namespace std::literals;
typedef std::chrono::high_resolution_clock Clock;

heartBeatClass::heartBeatClass(std::vector<sf::TcpSocket*> * _clientVector, sf::SocketSelector& _selector)
{
	//auto start = std::chrono::high_resolution_clock::now();
	//auto end = std::chrono::high_resolution_clock::now();
	//std::chrono::duration<double, std::milli> elapsed = end - start;

	//m_clintVector = _clientVector;
	m_selector = _selector;
}

heartBeatClass::~heartBeatClass()
{

}

void heartBeatClass::update(std::vector<Client*> _clientVector)
{
	//for all the clients on our list 
	for (auto it = _clientVector.begin(); it != _clientVector.end(); it++)
	{
		//store the time that the ping was sent
		auto currentTime = Clock::now();



		//get this from the client
		auto nextTime = Clock::now();
		//(*it)->setLastPingVal(currentTime)
		//send our current client a message containing the ping
		sf::Packet PING;
		PING << "PING";
		
		(*it)->getSocket()->send(PING);

		if (m_selector.wait(sf::milliseconds(500)))
		{
			auto ping = std::chrono::duration_cast<std::chrono::microseconds>(nextTime - currentTime).count();
			(*it)->setLastPingVal(ping);
		}
		else
		{
			(*it)->setTimeOuts((*it)->getTimeOuts() + 1);
		}



		//create and send a packet "PONG" 

		//Hold for return

		//if no return is found 

		//add one to the the time out counter


		//If this puts the client over 5 timeouts, set there connected to false

	}

	std::this_thread::sleep_for(5s);
}