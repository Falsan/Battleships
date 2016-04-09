#include "Validation.h"
#include <iostream>






int Valid::validIn(int high, int low)
{
	int input;
	do
	{
		std::cout << "Please enter a value between " << high << " and " << low << std::endl;
		std::cin >> input;

	} while ((input > high) || (input < low));


		return input;

}