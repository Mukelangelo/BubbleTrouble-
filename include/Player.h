#pragma once

#include "MovingObject.h"
#include "Weapon.h"

class Player : public MovingObject{
public:
	Player(sf::Vector2f pos = sf::Vector2f());

	void move(sf::Time deltaTime);
	void shoot();
	void handlePowers();

	void draw(sf::RenderWindow& window);

private:
	int m_lives = 3;
	std::vector< std::unique_ptr<Power> > m_powers; // maybe shared?
};