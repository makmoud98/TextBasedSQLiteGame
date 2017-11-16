#include "Food.h"

Food::Food(int p, int w, std::string n)
{
	price = p;
	weight = w;
	name = n;
	consumable = true;
}

void Food::print()
{

	std::cout 
		<< std::setw(5) << std::right << " "
		
		<< std::setw(15) << std::left <<
		name

		<< std::setw(10) << std::left <<
		price

		<< std::setw(10) << std::left <<
		weight

		<< std::setw(10) << std::left <<
		consumable

		<< std::endl;
}
