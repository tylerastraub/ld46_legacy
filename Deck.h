#pragma once

#include "Card.h"

#include <vector>

class Deck
{
public:
	Deck() = default;
	~Deck();

	void add_card(Card* card);
	void remove_card(int card_number);
	void move_card_to_top(int card_number);

	Card* get_top_of_deck();
	Card* get_card(int card_number);
	std::vector<Card*> get_deck();
	int get_deck_size();
private:
	std::vector<Card*> _cards;
};

