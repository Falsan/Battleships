#pragma once
#include <vector>
#include "InputAction.h"
#include "Client.h"

class inputHandeler
{
public:
	inputHandeler(std::vector<inputAction*> * m_actionList, std::vector<Client*> * clientList);
	~inputHandeler() = default;

	bool handelInputs();
	Client * findClientWithID(int _in);

	std::vector<inputAction*> *m_actionList;
	std::vector<Client*> * m_clientList;
private:

};