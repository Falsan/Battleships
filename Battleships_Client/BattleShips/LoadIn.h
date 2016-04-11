#pragma once
#include "Cell.h"
#include <vector>

class LoadIn
{
public:
	LoadIn()= default;
	~LoadIn()=default;

	static std::vector<Cell*> loadFile(std::string, std::vector<Cell*> saveVector);
	static bool saveFile(std::vector<Cell*>, std::string);

};

//void makeShip(int size, int orientation, std::pair<int, int> origin);