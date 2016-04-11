#pragma once

#include "Client.h"
#include "ChatLog.h"

class InputManager
{
public:
	InputManager(){};
	~InputManager(){};

	std::string pollInput(int &commandNumber, BoardManager * _BoardManager, ChatLog * _ChatLog);

protected:

private:
	std::string command;
};