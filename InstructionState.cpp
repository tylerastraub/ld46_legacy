#include "InstructionState.h"

void InstructionState::init()
{
	if (!_instruction_texture.loadFromFile("res/instruction_screen.png")) {
		std::cout << "Failed to load file "
			<< "res/instruction_screen.png" << std::endl;
	}

	_instruction_sprite.setTexture(_instruction_texture);
	_instruction_sprite.setPosition(0, 0);
}

void InstructionState::handle_event(sf::Event event)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
		set_next_state(new CardState());
		set_next_level("");
	}
}

void InstructionState::tick(sf::Time time_elapsed)
{

}

void InstructionState::render(sf::RenderWindow * window)
{
	window->draw(_instruction_sprite);
}
