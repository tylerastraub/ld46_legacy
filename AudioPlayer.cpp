#include "AudioPlayer.h"

AudioPlayer::AudioPlayer(std::map<std::string, sf::SoundBuffer*> sounds)
{
	_sounds = sounds;
}

AudioPlayer::~AudioPlayer()
{
	_current_song.stop();
}

void AudioPlayer::play_sound(std::string file, float vol) {
	if (_sounds.count(file)) {
		_sound.setBuffer(*_sounds[file]);
		_sound.setVolume(vol);
		_sound.play();
	}
	else {
		std::cout << "Sound does not exist: " << file << std::endl;
	}
}

void AudioPlayer::play_music(std::string file, float vol, bool loop) {
	if (!_current_song.openFromFile(file)) {
		std::cout << "Failed to load file " << file << std::endl;
	}
	else {
		_current_song.setLoop(loop);
		_current_song.setVolume(vol);
		_current_song.play();
	}
}

void AudioPlayer::stop_music() {
	if (_current_song.getStatus() == sf::Sound::Status::Playing) {
		_current_song.stop();
	}
}