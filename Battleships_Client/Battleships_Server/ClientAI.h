#pragma once
#include "Client.h"
#include "Board.h"


class AIClient : public ServerClient
{
public:
	AIClient(std::vector<Cell*>,int difficulty);
	~AIClient();

	void setAIBoard(std::vector<Cell*> _in) { m_AIBoard = _in; }
	std::vector<Cell*> getAIBoard() { return m_AIBoard; }

	bool AIShoot();

	void AILoadLevel();

protected:

private:
	std::vector <Cell*> m_AIBoard;

};