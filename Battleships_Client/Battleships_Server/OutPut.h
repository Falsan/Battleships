#include <vector>
#include "Cell.h"
#include <iostream>
#include "GameData.h"


class output
{
private:

public:
	static void printBoard(std::vector<Cell*>, gameData * _GD);
	static void printElement(int);

	template<typename T>
	static void PrintOut(T&);

	template<typename T>
	static void PrintOutNL(T&);

};