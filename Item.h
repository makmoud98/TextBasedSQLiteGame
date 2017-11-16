#pragma once
#include <string>
#include <iostream>
#include <iomanip>

class Item {
public:
	std::string name;
	int weight;
	int price;
	
	Item();
	Item(int p, int w, std::string n);

	virtual void print();
};