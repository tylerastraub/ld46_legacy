#include "GameEndState.h"

void GameEndState::init()
{
	if (!_main_font.loadFromFile("res/fonts/lucidia_typewriter.ttf")) {
		std::cout << "Failed to load file res/fonts/lucidia_typewriter.ttf"
			<< std::endl;
	}
}

void GameEndState::handle_event(sf::Event event) {}

void GameEndState::tick(sf::Time time_elapsed) {}

void GameEndState::render(sf::RenderWindow * window)
{
	sf::Text success_text;
	success_text.setFont(_main_font);
	success_text.setString("> code compiled\n> PROGRAM_FINISHED: true\n> press \'n\' to restart the game");
	success_text.setCharacterSize(24);
	success_text.setPosition(20, 720 - success_text.getGlobalBounds().height - 20);
	success_text.setFillColor(sf::Color(65, 255, 0));
	window->draw(success_text);
}
