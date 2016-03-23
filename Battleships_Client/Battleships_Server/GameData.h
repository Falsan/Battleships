#ifndef _GAMEDATA_
#define _GAMEDATA_



class gameData
{
public:
	int GetBoardDi() { return m_boardDimentions; };
	void setBoardDi(int _in) { m_boardDimentions = _in; };
private:
	int m_boardDimentions = 10;
};
#endif