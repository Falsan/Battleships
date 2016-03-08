#include <vector>
#include "Cell.h"

class board
{
public:
	board();
	~board();

	std::vector<Cell*> m_board;
	void createBoard();
	int m_boardSize = 50;
};