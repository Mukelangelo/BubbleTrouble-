#include "Controller.h"

Controller::Controller()
	: m_board(), m_player(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 2 * WALL_SIZE))
{}

void Controller::run(sf::RenderWindow& window) {
	sf::Event event;
	const sf::Time timerLimit = sf::seconds(0.1f);
	sf::Clock clock;
	sf::Time deltaTimePlayer;
	
	while (window.isOpen()) {
		window.clear(sf::Color::White);
		m_board.draw(window);
		m_player.draw(window);
		window.display();

		if (!eventHandler(event, window))
			return;

		if (clock.getElapsedTime() >= timerLimit)
			clock.restart();

		switch (event.type)
		{
		case sf::Event::KeyPressed:
			movementManger(deltaTimePlayer, clock);
			break;
		}
		m_player.handlePowers();
	}
}

bool Controller::eventHandler(sf::Event& event, sf::RenderWindow& window) {
	while (window.pollEvent(event)) {
		if ((event.type == sf::Event::Closed) ||
			((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape))) 
		{
			return false;
		}

		if (event.type == sf::Event::KeyPressed) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
				m_player.setDirection(sf::Keyboard::Right);

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
				m_player.setDirection(sf::Keyboard::Left);

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
				m_player.shoot();
		}
	}
	return true;
}

bool Controller::movementManger(sf::Time& deltaTime, sf::Clock& clock) {
	m_player.setLastLoc(); // set last location as current location
	deltaTime = clock.restart();
	if (!checkBoundries()) 
		return false;
	m_player.move(deltaTime);
	
	//manage collision here

	return true;
}
bool Controller::checkBoundries() {
	auto temp = m_player.getLocation();
	if (temp.x < WALL_SIZE) {
		m_player.setLocation(sf::Vector2f(WALL_SIZE, temp.y));
		return false;
	}
	if (temp.x + WALL_SIZE > WINDOW_WIDTH - WALL_SIZE) {
		m_player.setLocation(sf::Vector2f(WINDOW_WIDTH - 2 * WALL_SIZE, temp.y));
		return false;
	}

	return true;
}