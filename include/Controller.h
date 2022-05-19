#pragma once
#include "Board.h"
#include "Player.h"

class Controller {
public:
	// default c-stor
	Controller();
	// run the game
	void run(sf::RenderWindow& window);

private:
	bool eventHandler(sf::Event& event, sf::RenderWindow& window);
	bool movementManger(sf::Time& deltaTime, sf::Clock& clock);

	Board m_board;
	Player m_player;

};