#pragma once

#include "GameObject.h"

class MovingObject : public GameObject {
public:
	//MovingObject(sf::Vector2f loc, const sf::Texture& texture);

	virtual void setDirection(sf::Vector2f key);
	virtual void move(sf::Time deltaTime);
	virtual void DirectionImg(int dir) = 0;

	void setLastLoc();
	sf::Vector2f getLastLoc() const;

protected:
	sf::Vector2f m_direction; // movement direction
	sf::Vector2f m_lastLoc; // last location before the last movement

	float m_speedPerSecond;
};