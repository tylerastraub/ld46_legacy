#pragma once

#include "State.h"
#include "Card.h"
#include "Deck.h"
#include "Background.h"
#include "Level.h"
#include "FileIO.h"
#include "TransitionState.h"
#include "GameEndState.h"

class CardState : public State
{
public:
	CardState() = default;
	~CardState();

	void init() override;
	void handle_event(sf::Event event) override;
	void tick(sf::Time time_elapsed) override;
	void render(sf::RenderWindow* window) override;

	void check_collisions();
	void card_dropped();
	void check_card_pos();

	void win();

	void play_card_insert_audio();

	// there is no good reason for having 3 different collision methods lol
	bool is_mouse_colliding(sf::RectangleShape* rect);
	bool is_card_on_table();
	bool is_rect_colliding(sf::RectangleShape rect1, sf::RectangleShape rect2);
private:
	float _default_tick_count = 1.f / 144.f; // 1.f / number of ticks per second
	float _current_tick_count = _default_tick_count;

	Deck* _deck;
	Card* _selected_card;
	Card* _inserted_card = nullptr;
	sf::Font _card_font;
	std::vector<Card*> _accepted_cards;
	
	Background* _background;
	sf::Color _background_color;

	sf::RectangleShape _table_rect;
	sf::RectangleShape _card_insert_rect;

	sf::Text _info_text;

	AudioPlayer* _audio_player;

	// mouse stuff
	bool _mouse_leftclick = false;
	bool _mouse_rightclick = false;
	bool _move_card = false;
	bool _selection_released = true;
	float _mouseX;
	float _mouseY;
	float _last_mouseX;
	float _last_mouseY;
	float _mouseDX;
	float _mouseDY;
};

