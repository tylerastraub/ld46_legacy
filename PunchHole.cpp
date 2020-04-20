#include "PunchHole.h"

PunchHole::PunchHole() {
	_hole_rect = new sf::RectangleShape;
	_hole_rect->setSize(sf::Vector2f(_width * _scale, _height * _scale));
	_hole_rect->setOutlineThickness(2);
	_hole_rect->setOutlineColor(sf::Color(45, 45, 45));
	_hole_rect->setFillColor(sf::Color(0, 0, 0, 0));

	_audio_player = new AudioPlayer();
}

PunchHole::~PunchHole() {
	delete _hole_rect;
	delete _audio_player;
}

void PunchHole::set_position(float x, float y)
{
	_hole_rect->setPosition(sf::Vector2f(x, y));
}

void PunchHole::set_scale(float scale)
{
	_scale = scale;
	_hole_rect->setSize(sf::Vector2f(_width * _scale, _height * _scale));
	_hole_rect->setOutlineThickness(std::ceil(_scale));
}

sf::RectangleShape* PunchHole::get_rect()
{
	return _hole_rect;
}

void PunchHole::punch(bool make_sound, bool punched_by_user)
{
	if (!_punched) {
		_punched = 2;
		if (punched_by_user) {
			_user_punched = true;
			_hole_rect->setFillColor(sf::Color(40, 50, 40));
		}
		else {
			_hole_rect->setFillColor(sf::Color(40, 40, 100));
		}
		
		if (make_sound) {
			_audio_player->play_music("res/sound/hole_punch.wav", 100.f, false);
		}
	}
	else if (_user_punched) {
		_punched = false;
		_hole_rect->setFillColor(sf::Color(0, 0, 0, 0));

		if (make_sound) {
			_audio_player->play_music("res/sound/hole_punch.wav", 100.f, false);
		}
	}
}

bool PunchHole::is_punched()
{
	return _punched > 0;
}
