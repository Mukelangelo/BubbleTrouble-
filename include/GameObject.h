#pragma once
#include "macros.h"

class GameObject {
public:
	void draw(sf::RenderWindow& window);
	sf::Vector2f getLocation() const;
	void setLocation(const sf::Vector2f& loc);

protected:
	sf::Vector2f m_location; // location of the object
	sf::Sprite m_sprite; // image of the object
};