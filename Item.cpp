#include "Item.h"

Item::Item()
{
	name = "";
	weight = 0;
	price = 0;
}

Item::Item(int p, int w, std::string n)
{
	name = n;
	weight = w;
	price = p;
}

void Item::print()
{
	std::cout
		<< std::setw(5) << std::right << " "

		<< std::setw(15) << std::left <<
		name

		<< std::setw(10) << std::left <<
		price

		<< std::setw(10) << std::left <<
		weight

		<< std::endl;
}
