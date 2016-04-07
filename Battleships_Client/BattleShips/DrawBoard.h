
#pragma once
#include <vector>
#include "Cell.h"

class draw
{
public:
	draw() = default;
	~draw() = default;
private:

	static void drawBoard(std::vector<Cell*> _inboard);

};
