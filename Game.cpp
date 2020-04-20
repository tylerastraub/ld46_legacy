#include "Game.h"

Game::Game() {
	_window = new sf::RenderWindow(sf::VideoMode(1280, 720), "Keep it alive", sf::Style::Fullscreen);
	_window->setFramerateLimit(144);
	_window->setVerticalSyncEnabled(false);
	_window->setMouseCursorGrabbed(true);
	_window->setKeyRepeatEnabled(false);

	sf::Clock clock;
	float current_time = 0;
	float last_time = 0;
	int fps = 0;
	float fps_display_delay = 0.1;

	_next_state = new InstructionState();

	while (_window->isOpen()) {
		fps = 0;

		if (_next_state) {
			if (_current_state) {
				delete _current_state;
			}

			_current_state = _next_state;
			_next_state = nullptr;
			if (_current_state->get_next_level() != "END_GAME" &&
				_current_state->get_next_level() != "") {
				_current_state->set_level(_current_state->get_next_level());
			}
			_current_state->init();
		}

		sf::Event event;
		while (_window->pollEvent(event)) {
			if (event.type == sf::Event::Closed) {
				exit();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				exit();
			}

			if (sf::Keyboard::isKeyPressed(sf::Keyboard::N)) {
				_next_state = new InstructionState();
			}

			if (_current_state) {
				_current_state->handle_event(event);
			}
		}

		sf::Time time_elapsed = clock.restart(); // returns time passed in milliseconds
		current_time = time_elapsed.asSeconds();
		fps = 1.f / current_time - last_time;
		fps_display_delay -= current_time;
		last_time = current_time;
		if (fps_display_delay <= 0) {
			_window->setTitle("Keep it alive | FPS: " + std::to_string(fps));
			fps_display_delay = 0.1;
		}

		// tick method
		if (_current_state) {
			_current_state->tick(time_elapsed);
		}

		_window->clear(sf::Color(40, 40, 40));

		if (_current_state) {
			_current_state->render(_window);
		}

		if (_current_state) {
			if (_current_state->get_next_state()) {
				_next_state = _current_state->get_next_state();
				_next_state->set_next_level(_current_state->get_next_level());
			}
		}

		_window->display();

		if (_exit_flag) {
			_window->close();
		}
	}
}

Game::~Game() {
	delete _window;
	if (_current_state) {
		delete _current_state;
	}

	if (_next_state) {
		delete _next_state;
	}
}

void Game::change_state(State * next_state)
{
	_next_state = next_state;
}

void Game::exit()
{
	_exit_flag = true;
}
