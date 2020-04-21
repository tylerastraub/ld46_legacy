#include "Level.h"

/* Level is defined in a .txt file as follows:
 * LEVEL_FILE:res/levels/level1.txt
 * FILE_TYPE:LEVEL
 * NUM_OF_CARDS:2
 * STARTING_CARDS:1,1,0,0,1,1,0,1,0,1,1,1,0,0,1,0|1,1,0,1... etc.
 * NEXT_LEVEL:res/levels/level2.txt
 * No spaces, use | to separate each card. A 1 indicates that it
 * is supposed to be punched, while a 0 indicates the opposite.
 * Put commas between numbers and hyphens between lines.
 * NOTE: Each punchcard has 16x5 punchholes
 */

Level::Level(std::map<std::string, std::string> level)
{
	_level = level;
	std::string starting_cards = level["STARTING_CARDS"];
	_num_of_cards = std::stoi(level["NUM_OF_CARDS"]);
	_next_level = level["NEXT_LEVEL"];

	// this allows us to easily directly insert correct cards later
	for (int i = 0; i < _num_of_cards; ++i) {
		std::vector<int> blank_vec = {};
		_starting_cards.push_back(blank_vec);
	}

	int card = 0;
	int index = 0;
	while (index < starting_cards.length()) {
		if (starting_cards[index] == '0' || starting_cards[index] == '1') {
			_starting_cards[card].push_back(std::stoi(starting_cards.substr(index, 1)));
		}
		else if (starting_cards[index] == '|') {
			++card;
		}
		++index;
	}
}

// checks if every punch card is solved
// this algorithm is disgustingly ineffcient but we know input size is
// small so whatever
bool Level::cards_are_correct(std::vector<Card*> cards)
{
	// horizontal check
	for (auto it : cards) {
		for (int i = 0; i < 4; ++i) {
			int consecutive_zero_horizontal = 0;
			int consecutive_one_horizontal = 0;
			int balance_horizontal = 0;
			for (int j = 0; j < 16; ++j) {
				switch (it->punched_at(j, i)) {
					case 0:
						++consecutive_zero_horizontal;
						consecutive_one_horizontal = 0;
						++balance_horizontal;
						if (consecutive_zero_horizontal > 2) {
							return false;
						}
						break;
					case 1:
						++consecutive_one_horizontal;
						consecutive_zero_horizontal = 0;
						--balance_horizontal;
						if (consecutive_one_horizontal > 2) {
							return false;
						}
						break;
				}
			}
			
			if (balance_horizontal != 0) {
				return false;
			}
		}

		// vertical check
		for (int i = 0; i < 16; ++i) {
			int consecutive_zero_vertical = 0;
			int consecutive_one_vertical = 0;
			int balance_vertical = 0;
			for (int j = 0; j < 4; ++j) {
				switch (it->punched_at(i, j)) {
					case 0:
						++consecutive_zero_vertical;
						consecutive_one_vertical = 0;
						++balance_vertical;
						if (consecutive_zero_vertical > 2) {
							return false;
						}
						break;
					case 1:
						++consecutive_one_vertical;
						consecutive_zero_vertical = 0;
						--balance_vertical;
						if (consecutive_one_vertical > 2) {
							return false;
						}
						break;
				}
			}
			if (balance_vertical != 0) {
				return false;
			}
		}
	}

	return true;
}

int Level::get_num_of_cards()
{
	return _num_of_cards;
}

std::string Level::get_next_level()
{
	return _next_level;
}

std::string Level::get_level_string() {
	return _level["LEVEL_FILE"];
}

std::vector<std::vector<int>> Level::get_starting_cards() {
	return _starting_cards;
}