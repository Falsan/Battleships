#ifndef _GAMEMANAGER_
#define _GAMEMANAGER_
#include <vector>
#include "Board.h"
#include "Cell.h"
#include <memory>
#include "GameData.h"
#include <thread>
#include "Listern.h"

class gameManager {

public:
	gameManager(gameData * _GD);
	~gameManager() = default;

	listern m_listern;
	
	bool listern();

	bool logic();
	bool heartBeat();

	
	board * getBoard() { return m_gameBoard; };
private:
	board * m_gameBoard;
};

#endif