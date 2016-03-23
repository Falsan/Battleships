#include "GameManager.h"
#include <memory>
#include "GameData.h"


int main()
{
	gameData * m_GD = new gameData;
	std::unique_ptr<gameManager> Game;
	Game.reset(new gameManager(m_GD));
	
	return 0;
}