#pragma once


class Cell
{
public:
	Cell();
	~Cell() = default;
	unsigned short int m_cellType : 2;
	unsigned short int getCellType() { return m_cellType; };
};


/*
0 - empity
1 - Boat
2 - shot
3 - shot + boat
*/