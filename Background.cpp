#include "Background.h"

Background::Background()
{
	if (!_computer_texture.loadFromFile(_computer_filepath)) {
		std::cout << "Failed to load file from " << _computer_filepath
			<< std::endl;
	}

	_computer_sprite.setPosition(0, 0);
	_computer_sprite.setTexture(_computer_texture);

	if (!_tape_texture.loadFromFile(_tape_filepath)) {
		std::cout << "Failed to load file from " << _tape_filepath
			<< std::endl;
	}

	_tape1_sprite.setTexture(_tape_texture);
	_tape1_sprite.setPosition(355 + _tape1_sprite.getGlobalBounds().width / 2.f,
		193 + _tape1_sprite.getGlobalBounds().width / 2.f);
	_tape1_sprite.setOrigin(_tape1_sprite.getGlobalBounds().width / 2.f,
		_tape1_sprite.getGlobalBounds().height / 2.f);
	_tape1_sprite.setRotation(180.f);

	_tape2_sprite.setTexture(_tape_texture);
	_tape2_sprite.setPosition(449 + _tape2_sprite.getGlobalBounds().width / 2.f,
		193 + _tape2_sprite.getGlobalBounds().height / 2.f);
	_tape2_sprite.setOrigin(_tape2_sprite.getGlobalBounds().width / 2.f,
		_tape2_sprite.getGlobalBounds().height / 2.f);

	if (!_table_texture.loadFromFile(_table_filepath)) {
		std::cout << "Failed to load file from " << _table_filepath
			<< std::endl;
	}

	_table_sprite.setPosition(0, 120);
	_table_sprite.setTexture(_table_texture);

	if (!_right_background_texture.loadFromFile(_right_background_filepath)) {
		std::cout << "Failed to load file from " << _right_background_filepath
			<< std::endl;
	}

	_right_background_sprite.setPosition(680, 0);
	_right_background_sprite.setTexture(_right_background_texture);

	_audio_player = new AudioPlayer;
	_audio_player->play_music("res/sound/computer_fan.wav", 70.f, true);
}

Background::~Background() {
	delete _audio_player;
}

void Background::draw_background(sf::RenderWindow * window)
{
	// computer
	window->draw(_computer_sprite);

	// tape wheels
	window->draw(_tape1_sprite);
	window->draw(_tape2_sprite);

	// table
	window->draw(_table_sprite);

	// right bg
	// window->draw(_right_background_sprite);
}

void Background::tick()
{
	if (_game_over && _tape_rotate_speed > 0) {
		_tape_rotate_speed -= 0.005;
	}
	else if (_game_over) {
		_tape_rotate_speed = 0.f;
	}
	_tape1_sprite.rotate(_tape_rotate_speed);
	_tape2_sprite.rotate(-1 * _tape_rotate_speed);
}

void Background::game_over()
{
	_game_over = true;
	_audio_player->stop_music();
	_audio_player->play_music("res/sound/power_down.wav", 50.f, false);
}
