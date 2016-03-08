#include <vector>
#include "Board.h"
#include "Cell.h"
class gameManager {
public:
	gameManager();
	~gameManager();
	
	std::vector<Cell*> getBoard();

	board *m_gameBoard;

};