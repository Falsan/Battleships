#pragma once
#include <string>





class Client
{
public:

	std::string getClientID() { return clientID; }
	int getTimeOuts() { return timeOuts; }
	bool getconnected() { return connected; }

	void setClientID(std::string _in) { clientID = _in; }
	void setTimeOuts(int _in) { timeOuts = _in; }
	void setConnected(bool _in) { connected = _in; }


private:
	// the Id used to identify the user
	std::string clientID;

	//the number of times the user has failed a heart beat test
	int timeOuts = 0;

	bool connected = false;

};