#include "TransitionState.h"

#include "CardState.h"

void TransitionState::init()
{
	if (!_main_font.loadFromFile("res/fonts/lucidia_typewriter.ttf")) {
		std::cout << "Failed to load file res/fonts/lucidia_typewriter.ttf"
			<< std::endl;
	}
}

void TransitionState::handle_event(sf::Event event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		set_next_state(new CardState());
		set_next_level(get_next_level());
	}
}

void TransitionState::tick(sf::Time time_elapsed)
{

}

void TransitionState::render(sf::RenderWindow * window)
{
	sf::Text success_text;
	success_text.setFont(_main_font);
	success_text.setString("> code compiled successfully\n> click anywhere to continue");
	success_text.setCharacterSize(24);
	success_text.setPosition(20, 720 - success_text.getGlobalBounds().height - 20);
	success_text.setFillColor(sf::Color(65, 255, 0));
	window->draw(success_text);
}
