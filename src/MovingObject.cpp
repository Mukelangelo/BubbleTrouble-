#include "MovingObject.h"

void MovingObject::move(sf::Time deltaTime)
{
	//m_sprite.move(m_direction * m_speedPerSecond * deltaTime.asSeconds());
	//m_location = m_sprite.getPosition();
}

void MovingObject::setLocation(const sf::Vector2f& loc)
{
	//m_sprite.setPosition(loc);
	
	m_location = loc;
}

void MovingObject::setDirection(sf::Keyboard::Key key)
{
	switch (key)
	{
	case sf::Keyboard::Key::Left:
		m_direction = sf::Vector2f(-1, 0);
		//DirectionImg(Left);
		break;
	case sf::Keyboard::Key::Right:
		m_direction = sf::Vector2f(1, 0);
		//DirectionImg(Right);
		break;
	}
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