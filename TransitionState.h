#pragma once

#include "State.h"

class CardState;

class TransitionState : public State
{
public:
	TransitionState() = default;
	~TransitionState() = default;

	void init() override;
	void handle_event(sf::Event event) override;
	void tick(sf::Time time_elapsed) override;
	void render(sf::RenderWindow *window) override;
private:
	sf::Font _main_font;
};

