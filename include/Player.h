#pragma once

#include "MovingObject.h"

class Player : public MovingObject{
public:
	Player(sf::Vector2f pos = sf::Vector2f());

	void move(sf::Time deltaTime);
	void shoot();

	void draw(sf::RenderWindow& window);

private:
	int m_lives = 3;
	// insert vector of powers
};