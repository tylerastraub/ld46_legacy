#include "State.h"

void State::set_next_level(std::string level)
{
	_next_level = level;
}

void State::set_level(std::string level)
{
	FileIO fileIO;
	_level = new Level(fileIO.read_file(level, ":"));
}

void State::set_next_state(State * next_state)
{
	_next_state = next_state;
}

void State::set_audio_buffers(std::map<std::string, sf::SoundBuffer*> audio_buffers)
{
	_audio_buffers = audio_buffers;
}

State * State::get_next_state()
{
	return _next_state;
}

std::string State::get_next_level()
{
	return _next_level;
}

Level * State::get_level()
{
	return _level;
}

std::map<std::string, sf::SoundBuffer*> State::get_audio_buffers()
{
	return _audio_buffers;
}
