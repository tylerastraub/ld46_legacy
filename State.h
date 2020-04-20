#pragma once

#include <SFML/Graphics.hpp>

#include "Level.h"
#include "FileIO.h"

class State
{
public:
	State() = default;
	virtual ~State() = default;

	virtual void init() = 0;
	virtual void handle_event(sf::Event event) = 0;
	virtual void tick(sf::Time time_elapsed) = 0;
	virtual void render(sf::RenderWindow *window) = 0;

	void set_next_level(std::string level);
	void set_level(std::string level);
	void set_next_state(State* next_state);

	State* get_next_state();
	std::string get_next_level();
	Level* get_level();

private:
	State* _next_state = nullptr;
	std::string _next_level;
	Level* _level = nullptr;
};

