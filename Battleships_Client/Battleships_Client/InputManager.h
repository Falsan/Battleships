#pragma once

#include "Client.h"

class InputManager
{
public:
	InputManager(){};
	~InputManager(){};

	std::string pollInput();

protected:

private:
	std::string command;
};