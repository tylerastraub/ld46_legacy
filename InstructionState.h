#pragma once

#include "State.h"
#include "CardState.h"

class InstructionState : public State
{
public:
	InstructionState() = default;
	~InstructionState() = default;

	void init() override;
	void handle_event(sf::Event event) override;
	void tick(sf::Time time_elapsed) override;
	void render(sf::RenderWindow *window) override;
private:
	sf::Texture _instruction_texture;
	sf::Sprite _instruction_sprite;
};

