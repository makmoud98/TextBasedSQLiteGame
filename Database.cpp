#include "Database.h"

Database::Database(std::string filePath)
{
	pathToDB = filePath;
}

std::string Database::getQuestion(std::string progress)
{
	std::string question = "";
	try {
		sqlite::sqlite db(pathToDB);
		auto cur = db.get_statement();
		cur->set_sql("select content from questions where id = '" + progress + "'");
		cur->prepare();
		if (cur->step()) {
			question = cur->get_text(0);
		}
	}
	catch (sqlite::exception e)
	{
		std::cerr << e.what() << std::endl;
		return "";
	}
	return question;
}

std::string Database::getAnswers(std::string progress)
{
	std::string answer = "";
	try {
		sqlite::sqlite db(pathToDB);
		auto cur = db.get_statement();
		cur->set_sql("select content from answers where id = '" + progress + "'");
		cur->prepare();
		if (cur->step()) {
			answer = cur->get_text(0);
		}
	}
	catch (sqlite::exception e)
	{
		std::cerr << e.what() << std::endl;
		return "";
	}
	return answer;
}

std::vector<Item*> Database::getItems()
{
	std::vector<Item*> items;
	try {
		sqlite::sqlite db(pathToDB);
		auto cur = db.get_statement();
		cur->set_sql("select * from item");
		cur->prepare();
		int i = 0;
		while (cur->step()) {
			std::string name = cur->get_text(1);;
			int weight = cur->get_int(2);
			std::string consumable = cur->get_text(3);
			int price = cur->get_int(4);
			int damage = cur->get_int(5);
			if (consumable == "TRUE") {//food
				items.push_back(new Food(price, weight, name));
			}
			else if(damage != 0){//weapon
				double x = 44 + (price / 3) + (damage / 3);
				double r = ((double)rand() / (RAND_MAX));
				std::random_device rd; 
				std::mt19937 gen(rd());
				std::uniform_real_distribution<> dis(0, 1);
				int durability = (double)(x*dis(gen))+4;
				items.push_back(new Weapon(price, weight, name, damage, durability, getType(durability)));
			}
			else {//item
				items.push_back(new Item(price, weight, name));
			}
			i++;
		}
	}
	catch (sqlite::exception e)
	{
		std::cerr << e.what() << std::endl;
		return items;
	}
	return items;
}

std::string Database::getType(int durability)
{
	try {
		sqlite::sqlite db(pathToDB);
		auto cur = db.get_statement();
		cur->set_sql("select * from type");
		cur->prepare();
		std::string last;
		while (cur->step()) {
			if (durability < cur->get_int(2))
			{
				return cur->get_text(1);
			}
			else {
				last = cur->get_text(1);
			}
		}
		return last;
	}
	catch (sqlite::exception e)
	{
		std::cerr << e.what() << std::endl;
		return "";
	}
	return "";
}