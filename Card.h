#pragma once

#include <SFML/Graphics.hpp>
#include "PunchHole.h"

#include <iostream>

class Card
{
public:
	Card(std::string card_number);
	~Card();

	void set_position(float x, float y);
	void change_position(float dx, float dy);
	void draw_punchholes(sf::RenderWindow* window);
	void check_punchhole_collision(float mouseX, float mouseY);
	void set_minimode(bool mode);
	void set_mousepos(float mouseX, float mouseY);
	void set_punchholes(std::vector<int> card);

	sf::Sprite get_card_sprite();
	sf::RectangleShape* get_card_rect();
	std::string get_card_number();
	float get_scale();
	bool is_mini();
	bool punched_at(int x, int y);

private:
	sf::RectangleShape* _card_rect;
	sf::Texture _card_texture;
	sf::Sprite _card_sprite;
	std::string _image_filepath = "res/punch_card_template.png";

	std::string _card_number;

	int _punchholes_width = 16;
	int _punchholes_height = 4;
	PunchHole* _punchholes[16][4];

	bool _minimode = true;
	float _card_scale = 0.5;
	float _big_card_scale = 2.f;
	float _mini_card_scale = 0.5;

	float _mouseX;
	float _mouseY;
};
