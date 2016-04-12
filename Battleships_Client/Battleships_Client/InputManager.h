#pragma once

#include "Client.h"
#include "ChatLog.h"

class InputManager
{
public:
	InputManager(){};
	~InputManager(){};

	std::string pollInput(int &commandNumber, BoardManager * _BoardManager, ChatLog * _ChatLog, std::pair<int, int> &shot);
	std::pair<int, int> playerShot();

protected:

private:
	std::vector<int*> board;
	
};