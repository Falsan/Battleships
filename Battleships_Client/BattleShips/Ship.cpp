#include "Ship.h"

Ship::Ship(int size, int orientation, std::pair<int, int> origin)
{
	setSize(size);
	setOrientation(orientation);
	setPos(origin);
}