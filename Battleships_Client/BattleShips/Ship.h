#pragma once
#pragma once

#include <vector>

class Ship
{
public:

	Ship(int size, int orientation, std::pair<int, int> origin);
	~Ship() = default;
	int getSize() { return size; }
	void setSize(int wantedSize) { size = wantedSize; }
	int getOrientation() { return orientation; }
	void setOrientation(int wantedOrientation) { orientation = wantedOrientation; }
	std::pair<int, int> getPos() { return pos; }
	void setPos(int x, int y) { pos.first = x; pos.second = y; }
	void setPos(std::pair<int, int> origin) { pos = origin; }

protected:

private:

	int size;
	int orientation;
	std::pair<int, int> pos;
};