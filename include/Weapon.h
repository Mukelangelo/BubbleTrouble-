#pragma once

#include "Power.h"

class Weapon : public Power {
public:
	Weapon();

	void checkEnd();
	void activate(const sf::Vector2f& pos);
	void draw(sf::RenderWindow& window);

private:
	int m_type;
	bool m_shooting;
};