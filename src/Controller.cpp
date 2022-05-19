#include "Controller.h"

Controller::Controller()
	: m_board(), m_player()
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
	m_player.move(deltaTime);

	//manage collision here

	return true;
}