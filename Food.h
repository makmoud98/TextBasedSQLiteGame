#pragma once
#include "Item.h";

class Food : public Item {
public:
	bool consumable;

	Food(int p, int w, std::string n);

	void print() override;
};