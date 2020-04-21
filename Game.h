#pragma once

#include "State.h"
#include "InstructionState.h"

#include <SFML/Graphics.hpp>

class Game
{
public:
	Game();
	~Game();

	void change_state(State *next_state);
	void exit();
	void load_audio_buffers();

private:
	sf::RenderWindow *_window;
	State *_next_state;
	State *_current_state;
	bool _exit_flag = false;

	std::map<std::string, sf::SoundBuffer*> _audio_buffers;

	std::string _next_level;
};

