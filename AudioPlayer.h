#pragma once

#include <SFML/Audio.hpp>

#include <iostream>

class AudioPlayer
{
public:
	AudioPlayer() = default;
	~AudioPlayer() = default;

	void play_sound(std::string file, float vol);
	void play_music(std::string file, float vol, bool loop);
	void stop_music();
private:
	sf::Music _current_song;
};

