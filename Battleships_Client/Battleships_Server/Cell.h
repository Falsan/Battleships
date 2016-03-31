#ifndef _CELL_
#define _CELL_

class Cell
{
public:
	Cell();
	~Cell() = default;
	
	unsigned short int getCellType() { return m_cellType; };
	void setCellType(int cellTypeWanted);
private:
	unsigned short int m_cellType : 2;

};

#endif


/*
0 - empity
1 - Boat
2 - shot
3 - shot + boat
*/