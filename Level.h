#pragma once

#include "Card.h"

#include <map>
#include <vector>
#include <string>

class Level
{
public:
	Level(std::map<std::string, std::string> level);
	~Level() = default;

	bool cards_are_correct(std::vector<Card*> cards);

	int get_num_of_cards();
	std::string get_next_level();
	std::string get_level_string();
	std::vector<std::vector<int>> get_starting_cards();
private:
	std::vector<std::vector<int>> _starting_cards;
	int _num_of_cards = 0;
	std::string _next_level;
	std::map<std::string, std::string> _level;
};

