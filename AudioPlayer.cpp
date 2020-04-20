#include "AudioPlayer.h"

void AudioPlayer::play_sound(std::string file, float vol) {
	sf::SoundBuffer buffer;
	sf::Sound sound;
	if (!buffer.loadFromFile(file)) {
		std::cout << "Failed to load file " << file << std::endl;
	}
	else {
		sound.setBuffer(buffer);
		sound.setVolume(vol);
		sound.play();
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