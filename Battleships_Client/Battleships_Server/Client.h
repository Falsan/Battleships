#pragma once
#include <string>
#include <SFML\Network.hpp>

class Client
{
public:
	Client() = default;
	~Client() = default;
	std::string getClientID() { return clientID; }
	int getTimeOuts() { return timeOuts; }
	bool getconnected() { return connected; }
	float getLastPing() { return lastPingValue; }
	float getLastPong() { return lastPongValue; }
	sf::TcpSocket* getSocket() { return socket; }

	void setClientID(std::string _in) { clientID = _in; }
	void setTimeOuts(int _in) { timeOuts = _in; }
	void setConnected(bool _in) { connected = _in; }
	void setLastPingVal(float _in) { lastPingValue = _in; }
	void setLastPongVal(float _in) { lastPongValue = _in; }
	void setSocket(sf::TcpSocket* _in) { socket = _in; }

private:
	// the Id used to identify the user
	std::string clientID;

	//the number of times the user has failed a heart beat test
	int timeOuts = 0;
	float lastPingValue;
	float lastPongValue;
	bool connected = false;
	sf::TcpSocket* socket;

};