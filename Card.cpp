#include "Card.h"

Card::Card(std::string card_number)
{
	_card_number = card_number;

	_card_rect = new sf::RectangleShape;
	if (!_card_texture.loadFromFile(_image_filepath)) {
		std::cout << "Failed to load file at " << _image_filepath << std::endl;
	}
	_card_sprite.setTexture(_card_texture);
	_card_sprite.setScale(sf::Vector2f(_card_scale, _card_scale));
	_card_rect->setSize(sf::Vector2f(_card_sprite.getGlobalBounds().width,
		_card_sprite.getGlobalBounds().height));

	for (int i = 0; i < _punchholes_width; ++i) {
		for (int j = 0; j < _punchholes_height; ++j) {
			_punchholes[i][j] = new PunchHole();
			_punchholes[i][j]->set_scale(_card_scale);
		}
	}
}

Card::~Card() {
	delete _card_rect;

	for (int i = 0; i < _punchholes_width; ++i) {
		for (int j = 0; j < _punchholes_height; ++j) {
			delete _punchholes[i][j];
		}
	}
}

void Card::set_position(float x, float y)
{
	// _card_rect is for logic, _card_sprite is for actual image
	_card_rect->setPosition(x, y);
	_card_sprite.setPosition(x, y);

	for (int i = 0; i < _punchholes_width; ++i) {
		for (int j = 0; j < _punchholes_height; ++j) {
			// 52 is magic number for x offset, 46 is magic number for y offset
			// multiplication is for spacing between punchholes
			_punchholes[i][j]->set_position((13 * _card_scale * i) + x + (27 * _card_scale),
				(16.5 * _card_scale * j) + y + (23 * _card_scale));
		}
	}
}

void Card::change_position(float dx, float dy) {
	_card_rect->move(dx, dy);
	_card_sprite.move(dx, dy);

	for (int i = 0; i < _punchholes_width; ++i) {
		for (int j = 0; j < _punchholes_height; ++j) {
			_punchholes[i][j]->get_rect()->move(dx, dy);
		}
	}
}

void Card::draw_punchholes(sf::RenderWindow * window)
{
	for (int i = 0; i < _punchholes_width; ++i) {
		for (int j = 0; j < _punchholes_height; ++j) {
			window->draw(*_punchholes[i][j]->get_rect());
		}
	}
}

// return true if we want punchhole sound to occur
bool Card::check_punchhole_collision(float mouseX, float mouseY)
{
	if (!_minimode) {
		for (int i = 0; i < _punchholes_width; ++i) {
			for (int j = 0; j < _punchholes_height; ++j) {
				sf::RectangleShape* rect = _punchholes[i][j]->get_rect();
				if (mouseX >= rect->getPosition().x &&
					mouseX < rect->getPosition().x + rect->getGlobalBounds().width &&
					mouseY >= rect->getPosition().y &&
					mouseY < rect->getPosition().y + rect->getGlobalBounds().height) {
					return _punchholes[i][j]->punch(true, true);
				}
			}
		}

		return false;
	}

	return false;
}

void Card::set_minimode(bool mode)
{
	if (_minimode == mode) return;

	_minimode = mode;
	if (_minimode) {
		_card_scale = _mini_card_scale;
		_card_sprite.setScale(_mini_card_scale, _mini_card_scale);
		for (int i = 0; i < _punchholes_width; ++i) {
			for (int j = 0; j < _punchholes_height; ++j) {
				_punchholes[i][j]->set_scale(_mini_card_scale);
			}
		}
	}
	else {
		_card_scale = _big_card_scale;
		_card_sprite.setScale(_big_card_scale, _big_card_scale);
		for (int i = 0; i < _punchholes_width; ++i) {
			for (int j = 0; j < _punchholes_height; ++j) {
				_punchholes[i][j]->set_scale(_big_card_scale);
			}
		}
	}

	_card_rect->setSize(sf::Vector2f(_card_sprite.getGlobalBounds().width,
		_card_sprite.getGlobalBounds().height));
	set_position(_mouseX - _card_rect->getGlobalBounds().width / 2,
		_mouseY - _card_rect->getGlobalBounds().height / 2);
}

void Card::set_mousepos(float mouseX, float mouseY)
{
	_mouseX = mouseX;
	_mouseY = mouseY;
}

// only used for card initialization as it goes through every punchhole
void Card::set_punchholes(std::vector<int> card) {
	for (int j = 0; j < _punchholes_height; ++j) {
		for (int i = 0; i < _punchholes_width; ++i) {
			if (!_punchholes[i][j]->is_punched() && 
				card[i + (j * _punchholes_width)] == 1) {
				_punchholes[i][j]->punch(false, false);
			}
		}
	}
}

sf::Sprite Card::get_card_sprite()
{
	return _card_sprite;
}

sf::RectangleShape* Card::get_card_rect() {
	return _card_rect;
}

std::string Card::get_card_number()
{
	return _card_number;
}

float Card::get_scale()
{
	return _card_scale;
}

bool Card::is_mini()
{
	return _minimode;
}

bool Card::punched_at(int x, int y)
{
	return _punchholes[x][y]->is_punched();
}

