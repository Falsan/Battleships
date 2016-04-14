#include "GameManager.h"
#include <memory>


// smart pointer ensures that all subsquent objects are 
//deconstructed at program termination
int main()
{
	std::unique_ptr<GameManager> Game;
	Game.reset(new GameManager());
	
	return 0;
}