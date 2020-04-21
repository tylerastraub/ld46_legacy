#pragma once

#include <SFML/Audio.hpp>

#include <iostream>
#include <map>

class AudioPlayer
{
public:
	AudioPlayer(std::map<std::string, sf::SoundBuffer*> sounds);
	~AudioPlayer();

	void play_sound(std::string file, float vol);
	void play_music(std::string file, float vol, bool loop);
	void stop_music();
private:
	std::map<std::string, sf::SoundBuffer*> _sounds;
	sf::Music _current_song;
	sf::Sound _sound;
};

