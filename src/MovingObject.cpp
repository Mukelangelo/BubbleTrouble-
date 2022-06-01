#include "MovingObject.h"

void MovingObject::move(sf::Time deltaTime)
{
	//m_sprite.move(m_direction * m_speedPerSecond * deltaTime.asSeconds());
	//m_location = m_sprite.getPosition();
}


void MovingObject::setDirection(sf::Vector2f key)
{
	m_direction = key;
}

void MovingObject::setLastLoc()
{
	m_lastLoc = m_location;
}

//=======================================================================================
sf::Vector2f MovingObject::getLastLoc() const
{
	return m_lastLoc;
}