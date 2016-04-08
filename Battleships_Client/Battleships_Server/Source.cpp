#include "GameManager.h"
#include <memory>



int main()
{
	std::unique_ptr<GameManager> Game;
	Game.reset(new GameManager());
	
	return 0;
}