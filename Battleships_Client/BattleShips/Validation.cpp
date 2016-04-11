#include "Validation.h"
#include <iostream>






int Valid::validIn(int high, int low)
{
	int input;
	do
	{
		std::cout << "Please enter a value between " << low+1 << " and " << high-1  << std::endl;
		std::cin >> input;

	} while ((input > high) || (input < low));


		return input;

}