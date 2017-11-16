#include "Weapon.h"


Weapon::Weapon(int p, int w, std::string n, int dmg, int dur, std::string t)
{
	price = p;
	weight = w;
	name = n;
	damage = dmg;
	durability = dur;
	type = t;
}

void Weapon::print()

{
	std::cout 
		<< std::setw(5) << std::right << " "

		<< std::setw(15) << std::left <<
		name 

		<< std::setw(10) << std::left <<
		price 

		<< std::setw(10) << std::left <<
		weight

		<< std::setw(12) << std::left <<
		damage 

		<< std::setw(8) << std::left << 
		durability

		<< std::setw(10) << std::left <<
		type 

		<< std::endl;
	
	
}
