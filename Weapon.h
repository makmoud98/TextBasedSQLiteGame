#pragma once
#include "Item.h"

class Weapon : public Item {
public:
	int damage;
	int durability;
	std::string type;

	Weapon(int p, int w, std::string n, int dmg, int dur, std::string t);

	void print() override;
};