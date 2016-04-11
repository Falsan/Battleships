#pragma once

#include "Client.h"

class InputManager
{
public:
	InputManager(){};
	~InputManager(){};

	std::string pollInput(int &commandNumber);

protected:

private:
	std::string command;
};