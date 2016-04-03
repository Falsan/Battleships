#include <iostream>
#include "Helper.h"

void clearScreen()
{
	int clearScreenCount = 0;
	while (clearScreenCount != 100)
	{
		std::cout << std::endl;
		clearScreenCount++;
	}
}