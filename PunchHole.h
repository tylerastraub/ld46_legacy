#pragma once

#include <SFML/Graphics.hpp>

#include <cmath>

class PunchHole
{
public:
	PunchHole();
	~PunchHole();

	void set_position(float x, float y);
	void set_scale(float scale);
	
	sf::RectangleShape* get_rect();
	bool punch(bool make_sound, bool punched_by_user);

	bool is_punched();

private:
	int _punched = 0;
	bool _user_punched = false;
	sf::RectangleShape* _hole_rect;
	float _width = 8;
	float _height = 10;
	float _scale = 2.f;
};

