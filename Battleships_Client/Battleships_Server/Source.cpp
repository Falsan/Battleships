#include "GameManager.h"
#include <memory>
#include "GameData.h"


int main()
{
	gameData * m_GD = new gameData;
	std::unique_ptr<GameManager> Game;
	Game.reset(new GameManager(m_GD));
	
	return 0;
}