#pragma once

#include <SFML/Graphics.hpp>
#include "AudioPlayer.h"

#include <iostream>

class Background
{
public:
	Background();
	~Background();

	void draw_background(sf::RenderWindow* window);
	void tick();
	void game_over();
private:
	float _tape_rotate_speed = 1.5;
	bool _game_over = false;

	sf::Sprite _computer_sprite;
	sf::Sprite _tape1_sprite;
	sf::Sprite _tape2_sprite;
	sf::Sprite _table_sprite;
	sf::Sprite _right_background_sprite;

	sf::Texture _table_texture;
	sf::Texture _computer_texture;
	sf::Texture _tape_texture;
	sf::Texture _right_background_texture;

	std::string _table_filepath = "res/table.png";
	std::string _computer_filepath = "res/computer.png";
	std::string _tape_filepath = "res/tape_wheel.png";
	std::string _right_background_filepath = "res/right_background.png";

	AudioPlayer* _audio_player;
};

