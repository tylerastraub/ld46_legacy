#pragma once

#include "State.h"

class GameEndState : public State
{
public:
	GameEndState() = default;
	~GameEndState() = default;

	void init() override;
	void handle_event(sf::Event event) override;
	void tick(sf::Time time_elapsed) override;
	void render(sf::RenderWindow *window) override;
private:
	sf::Font _main_font;
};

