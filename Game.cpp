#define CATCH_CONFIG_MAIN
#include <iostream>
#include <string>
#include <sstream>
#include <algorithm>
#include <thread>   
#include <chrono> 
#include <iomanip>
#include "catch.hpp"
#include "Database.h"

std::string getInput() {
	std::string input;
	std::cin >> input;
	std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	while (input.compare("a") != 0 && input.compare("b") != 0 && input.compare("c") != 0)
	{
		std::cout << input << " is not a valid response. Please try again." << "\n";
		std::cin >> input;
		std::transform(input.begin(), input.end(), input.begin(), ::tolower);
	}
	return input;
}

SCENARIO("database class can be used to retrieve questions, answers, items, and types")
{
	GIVEN("a predefined database with question, answers, item, and type tables")
	{
		Database db("game.db");
		THEN("query a few random questions from the database")
		{
			REQUIRE(db.getQuestion("1aa") == "Hello?! Can you hear me?!");
			REQUIRE(db.getQuestion("1abc") == "Believe me or not, it doesn't matter.");
			REQUIRE(db.getQuestion("1abb") == "I don't know, I just tried a random number and here we are talking.");
		}
		THEN("query a few random answers from the database")
		{
			REQUIRE(db.getAnswers("1aab") == "A. 'How come? Where are you?'\nB. 'Die? Why?'\nC. 'Can I somehow help you?'");
			REQUIRE(db.getAnswers("1abb") == "A. 'It can't be true.'\nB. 'Lucky you.'\nC. 'Oh really?'");
			REQUIRE(db.getAnswers("1a") == "A. Answer the call.\nB. Hang up and put the phone in your pocket.\nC. Leave it on the ground and continue going home.");
		}
		THEN("query the list of item names and compare against our list")
		{
			std::string item_names[16] = { "Water","Cokecole","Lemonade","Axe","Shovel","Lockpicks","Rations","Cake","Chocolate","Sword","Pebble","Rocks","Dirt","Dead Rat","Screws","Phone" };
			int item_prices[16] = { 2,3,3,15,10,2,4,5,2,25,0,0,0,0,2,58 };
			int item_damages[16] = { 0,0,0,5,3,0,0,0,0,8,1,2,0,0,0,0 };
			bool item_not_consumable[16] = { false, false, false, true, true, true, false, false, false, true, true, true, true, false, true, true };
			std::vector<Item*> items = db.getItems();
			REQUIRE(items.size() == (sizeof(item_names) / sizeof(*item_names)));
			for (int i = 0; i < items.size(); i++) {
				REQUIRE(items[i]->name == item_names[i]);
				REQUIRE(items[i]->price == item_prices[i]);
				//REQUIRE(((Weapon*)items[i])->damage == item_damages[i]);
				//REQUIRE(((Food*)items[i])->consumable == item_consumable[i]);
			}
		}
		THEN("query the different types and their values to make sure they generate valid info")
		{
			REQUIRE(db.getType(5) == "Poor");
			REQUIRE(db.getType(14) == "Ok");
			REQUIRE(db.getType(22) == "Good");
			REQUIRE(db.getType(30) == "Excellent");
			REQUIRE(db.getType(38) == "Supreme");
			REQUIRE(db.getType(50) == "Supreme");
		}
	}
}
SCENARIO("test the game")
{
	Database db("game.db");

	bool game_over = false;
	int chapter = 1;
	std::string progress = "";

	std::vector<Item*> items = db.getItems();
	std::cout << "\n\n";
	std::cout << std::setw(28) << std::right << "" << "----TEXTMART----";
	std::cout << std::setw(35) << std::right << "\n" << "|____________________________________________________________________|" << "\n\n\n";

	std::cout
		<< std::setw(5) << std::right << " "

		<< std::setw(10) << std::left <<
		"Name"
		<< std::setw(10) << std::left <<
		"Value"
		<< std::setw(10) << std::left <<
		"Weight"
		<< std::setw(10) << std::left <<
		"Damage"
		<< std::setw(15) << std::left <<
		"Durability"
		<<
		"Type"
		<<
		"\n |__________________________________________________________________|\n" << std::endl;


	for (int i = 0; i < items.size(); i++) {
		items[i]->print();


	}
	std::cout << "\n |___________________________________________________________________|\n\n\n";



	while (!game_over) {
		std::ostringstream convert;
		convert << chapter;
		std::string question = db.getQuestion(convert.str() + progress);
		std::string answers = db.getAnswers(convert.str() + progress);
		std::cout << question << "\n";
		if (answers == "") {
			std::cout << "\n\n" << "GAME OVER" << "\n\n\n";
			game_over = true;
			break;
		}
		else {
			std::cout << answers << "\n";
			std::string input = getInput();
			progress += input;
			if (progress.length() == 4) {
				progress = "****";
			}
		}
		for (int i = 0; i < 20; i++) {
			std::cout << ". ";
			std::this_thread::sleep_for(std::chrono::milliseconds(50));
		}
		std::cout << '\n';
	}
}