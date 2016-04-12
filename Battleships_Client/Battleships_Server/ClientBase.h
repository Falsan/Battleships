#pragma once
#include <vector>
#include "DrawBoard.h"
#include "Cell.h"

class ClientBase
{
public:
	ClientBase();
	~ClientBase()=default;

	void setUpBoard(std::vector <int> _ShipPos);

	void setPlayersBoard(std::vector <Cell*> _in) { m_PlayersBoard = _in; }
	std::vector <Cell*> getPlayersBoard() { return m_PlayersBoard; }
	bool isAI = false;
private:
	std::vector <Cell*> m_PlayersBoard;

};


