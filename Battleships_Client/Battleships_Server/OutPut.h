#include <vector>
#include "Cell.h"
#include <iostream>


class output
{
private:

public:
	static void printBoard(std::vector<Cell*>);
	static void printElement(int);

	template<typename T>
	static void PrintOut(T&);

	template<typename T>
	static void PrintOutNL(T&);

};