#pragma once
#include <iostream>
#include <string>
#include <vector>
#include <random>
#include "libsqlite.hpp"
#include "Item.h"
#include "Weapon.h"
#include "Food.h"

class Database {
private:
	std::string pathToDB;
public:
	Database(std::string filePath);
	std::string getQuestion(std::string progress);
	std::string getAnswers(std::string progress);
	std::vector<Item*> getItems();
	std::string getType(int durability);
};