#include "GameObject.h"

void GameObject::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

sf::Vector2f GameObject::getLocation() const
{
	return m_location;
}

void GameObject::setLocation(const sf::Vector2f& loc)
{
	m_sprite.setPosition(loc);
	m_location = loc;
}