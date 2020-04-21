#include "Deck.h"

Deck::~Deck()
{
	for (int i = 0; i < _cards.size(); ++i) {
		delete _cards[i];
	}
}

void Deck::add_card(Card* card)
{
	_cards.push_back(card);
}

void Deck::remove_card(int card_number)
{
	auto it = _cards.begin();
	while(it != _cards.end()) {
		if (std::stoi((*it)->get_card_number()) == card_number) {
			_cards.erase(it);
			break;
		}
		else {
			++it;
		}
	}
}

void Deck::move_card_to_top(int card_number)
{
	for (auto it = _cards.begin(); it != _cards.end(); ++it) {
		if (std::stoi((*it)->get_card_number()) == (card_number)) {
			std::rotate(_cards.begin(), it, it + 1);
		}
	}
}

Card* Deck::get_top_of_deck()
{
	if (_cards.size() == 0) {
		return nullptr;
	}

	return _cards[0];
}

Card* Deck::get_card(int card_number)
{
	for (auto it = _cards.begin(); it != _cards.end(); ++it) {
		if (std::stoi((*it)->get_card_number()) == (card_number)) {
			return *it;
		}
	}

	return nullptr;
}

std::vector<Card*> Deck::get_deck()
{
	return _cards;
}

int Deck::get_deck_size()
{
	return _cards.size();
}
