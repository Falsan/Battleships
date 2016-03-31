#include "Cell.h"


Cell::Cell()
{
	m_cellType = 0;
}

void Cell::setCellType(int cellTypeWanted)
{
	m_cellType = cellTypeWanted;
}

/*
0 - empity
1 - Boat
2 - shot
3 - shot + boat
*/