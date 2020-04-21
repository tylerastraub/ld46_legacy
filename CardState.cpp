#include "CardState.h"

CardState::~CardState()
{
	_audio_player->stop_music();

	delete _deck;
	delete _background;
	delete _audio_player;
}

void CardState::init()
{
	_audio_player = new AudioPlayer(get_audio_buffers());
	_background = new Background(get_audio_buffers());
	_background_color = sf::Color(40, 40, 40);

	if (!_card_font.loadFromFile("res/fonts/lucidia_typewriter.ttf")) {
		std::cout << "Failed to load font res/fonts/lucidia_unicode.ttf" << std::endl;
	}

	_table_rect.setPosition(90, 600);
	_table_rect.setSize(sf::Vector2f(382, 40));
	_table_rect.setFillColor(sf::Color(50, 50, 50, 150));

	_card_insert_rect.setPosition(280, 360);
	_card_insert_rect.setSize(sf::Vector2f(11, 76));
	_card_insert_rect.setFillColor(sf::Color(50, 50, 50, 150));

	_info_text.setCharacterSize(14);
	_info_text.setFont(_card_font);
	_info_text.setFillColor(sf::Color::White);

	// level loading
	_deck = new Deck();
	if (get_level() == nullptr) {
		set_level("res/levels/level1.txt");
	}

	set_next_level(get_level()->get_next_level());

	for (int i = 0; i < get_level()->get_num_of_cards(); ++i) {
		_deck->add_card(new Card("0" + std::to_string(i)));
		_deck->get_card(i)->set_position(_table_rect.getPosition().x + i * 125,
			615);
		_deck->get_card(i)->set_punchholes(get_level()->get_starting_cards()[i]);
	}
	_selected_card = _deck->get_top_of_deck();
}

void CardState::handle_event(sf::Event event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
		_mouse_leftclick = true;
	}
	else {
		_mouse_leftclick = false;
	}

	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Right)) {
		_mouse_rightclick = true;
	}
	else {
		_mouse_rightclick = false;
		_selection_released = true;
	}

	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R)) {
		set_next_state(new CardState());
		set_next_level(get_level()->get_level_string());	
	}
}

void CardState::tick(sf::Time time_elapsed)
{
	_current_tick_count -= time_elapsed.asSeconds();
	if (_current_tick_count <= 0) {
		_background->tick();
		_current_tick_count = _default_tick_count;

		_mouseDX = _mouseX - _last_mouseX;
		_mouseDY = _mouseY - _last_mouseY;
		_last_mouseX = _mouseX;
		_last_mouseY = _mouseY;

		if (_selected_card) {
			check_collisions();

			if (!_mouse_leftclick) {
				if (_move_card) {
					card_dropped();
				}
				_move_card = false;
			}

			if (_move_card) {
				check_card_pos();
			}
		}

		if (_inserted_card) {
			_inserted_card->change_position(0.4f, 0);
			if (_inserted_card->get_card_rect()->getPosition().x > 280) {
				_accepted_cards.push_back(_inserted_card);
				_inserted_card = nullptr;
				_info_text.setString("");
				_audio_player->stop_music();
				if (_deck->get_deck_size() == 0) {
					if (get_level()->cards_are_correct(_accepted_cards)) {
						win();
					}
					else {
						_background->game_over();
						_info_text.setString(
							"incorrect instructions, shutting down (press R to restart)"
							);
						_info_text.setFillColor(sf::Color(255, 30, 30));
						_audio_player->stop_music();
					}
				}
			}
		}
	}
}

// left side is 680x720, right side is 600x720
void CardState::render(sf::RenderWindow* window)
{
	// these have to be here instead of tick() because they need RenderWindow
	_mouseX = sf::Mouse::getPosition(*window).x;
	_mouseY = sf::Mouse::getPosition(*window).y;

	sf::Text card_number;
	card_number.setFont(_card_font);
	card_number.setFillColor(sf::Color(45, 45, 45));

	// right background
	sf::RectangleShape right_background;
	right_background.setPosition(680, 0);
	right_background.setFillColor(sf::Color(40, 50, 40));
	right_background.setSize(sf::Vector2f(600, 720));
	window->draw(right_background);

	// first pass drawing punchcards - draw all cards that are big/on the right
	for (int i = _deck->get_deck_size() - 1; i >= 0; --i) {
		Card* c = _deck->get_deck()[i];
		if (!c->is_mini()) {
			window->draw(c->get_card_sprite());
			card_number.setString(c->get_card_number());
			card_number.setPosition(c->get_card_rect()->getPosition() +
				sf::Vector2f(6 * c->get_scale(), 4 * c->get_scale()));
			card_number.setCharacterSize(10 * c->get_scale());
			window->draw(card_number);
			c->draw_punchholes(window);
		}
	}

	// draw left background image and card being inserted (if there is one)
	sf::RectangleShape left_background(sf::Vector2f(680, 720));
	left_background.setFillColor(sf::Color(180, 180, 255));
	window->draw(left_background);
	if (_inserted_card) {
		window->draw(_inserted_card->get_card_sprite());
		_inserted_card->draw_punchholes(window);
	}
	_background->draw_background(window);

	// second pass - draw mini cards with rectangle covering anything on the right
	for (int i = _deck->get_deck_size() - 1; i >= 0; --i) {
		Card* c = _deck->get_deck()[i];
		if (c->is_mini()) {
			window->draw(c->get_card_sprite());
			card_number.setString(c->get_card_number());
			card_number.setPosition(c->get_card_rect()->getPosition() +
				sf::Vector2f(6 * c->get_scale(), 4 * c->get_scale()));
			card_number.setCharacterSize(10 * c->get_scale());
			window->draw(card_number);
			c->draw_punchholes(window);
		}
	}

	// draw info text
	if (_info_text.getString().getSize() != 0) {
		_info_text.setPosition(340 - _info_text.getGlobalBounds().width / 2.f,
			10);
		window->draw(_info_text);
	}
}

void CardState::check_collisions()
{
	std::vector<Card*> deck = _deck->get_deck();
	for (int i = 0; i < deck.size(); ++i) {
		if (is_mouse_colliding(deck[i]->get_card_rect())
			&& _mouse_leftclick
			&& !_move_card) {
			_move_card = true;
			_selected_card = deck[i];
			_deck->move_card_to_top(std::stoi(_selected_card->get_card_number()));
			break;
		}

		if (is_mouse_colliding(deck[i]->get_card_rect())
			&& _mouse_rightclick
			&& _selection_released) {
			_selected_card = deck[i];
			if (_selected_card->check_punchhole_collision(_mouseX, _mouseY)) {
				_audio_player->play_sound("res/sound/hole_punch.wav", 100.f);
			}
			_deck->move_card_to_top(std::stoi(_selected_card->get_card_number()));
			_selection_released = false;
			break;
		}
	}

	if (_mouse_leftclick) {
		if (is_rect_colliding(*_selected_card->get_card_rect(), _card_insert_rect) &&
			_inserted_card == nullptr) {
			_info_text.setString("insert card into slot");
		}
		else if (_inserted_card == nullptr) {
			_info_text.setString("");
		}
	}
}

void CardState::card_dropped()
{
	if (is_rect_colliding(*_selected_card->get_card_rect(), _card_insert_rect) &&
		_inserted_card == nullptr) {
		_info_text.setString("inserting card...");
		_inserted_card = _selected_card;
		play_card_insert_audio();
		_deck->remove_card(std::stoi(_selected_card->get_card_number()));
		_selected_card = _deck->get_top_of_deck();
		_inserted_card->set_position(162, 372);
	}
	else if (!is_card_on_table() && _selected_card->is_mini()) {
		float x = _selected_card->get_card_rect()->getPosition().x;

		if (x < _table_rect.getPosition().x) {
			_selected_card->set_position(_table_rect.getPosition().x, 615);
		}
		else if (x > _table_rect.getPosition().x
			+ _table_rect.getSize().x) {
			_selected_card->set_position(_table_rect.getPosition().x
				+ _table_rect.getSize().x, 615);
		}
		else {
			_selected_card->set_position(x, 615);
		}
	}
}

void CardState::check_card_pos()
{
	if (_mouseX < 680) {
		_selected_card->set_mousepos(_mouseX, _mouseY);
		if (_selected_card->is_mini()) {
			_selected_card->change_position(_mouseDX, _mouseDY);
		}
		_selected_card->set_minimode(true);
	}
	else {
		_selected_card->set_mousepos(_mouseX, _mouseY);
		if (!_selected_card->is_mini()) {
			_selected_card->change_position(_mouseDX, _mouseDY);
		}
		_selected_card->set_minimode(false);
	}
}

void CardState::win()
{
	if (get_level()->get_next_level() == "END_GAME") {
		set_next_state(new GameEndState());
		get_next_state()->set_next_level("");
	}
	else {
		set_next_state(new TransitionState());
		get_next_state()->set_next_level(get_level()->get_next_level());
	}
}

bool CardState::is_mouse_colliding(sf::RectangleShape* rect)
{
	if (_mouseX >= rect->getPosition().x &&
		_mouseX < rect->getPosition().x + rect->getGlobalBounds().width &&
		_mouseY >= rect->getPosition().y &&
		_mouseY < rect->getPosition().y + rect->getGlobalBounds().height) {
		return true;
	}

	return false;
}

bool CardState::is_card_on_table()
{
	float x = _selected_card->get_card_rect()->getPosition().x;
	float y = _selected_card->get_card_rect()->getPosition().y;
	
	if (x >= _table_rect.getPosition().x &&
		x < _table_rect.getPosition().x + _table_rect.getGlobalBounds().width &&
		y >= _table_rect.getPosition().y &&
		y < _table_rect.getPosition().y + _table_rect.getGlobalBounds().height) {
		return true;
	}

	return false;
}

bool CardState::is_rect_colliding(sf::RectangleShape rect1, sf::RectangleShape rect2)
{
	float x1 = rect1.getPosition().x;
	float y1 = rect1.getPosition().y;
	float x2 = rect2.getPosition().x;
	float y2 = rect2.getPosition().y;

	if (x1 < x2 + rect2.getGlobalBounds().width &&
		x1 + rect1.getGlobalBounds().width > x2 &&
		y1 < y2 + rect2.getGlobalBounds().height &&
		y1 + rect1.getGlobalBounds().height > y2) {
		return true;
	}

	return false;
}

void CardState::play_card_insert_audio() {
	_audio_player->play_music("res/sound/card_insert.wav", 100.f, true);
	// this is a dumb workaround so the AudioPlayer doesn't dissapear until
	// card is fully inserted
}