#include "Weapon.h"

Weapon::Weapon() : m_shooting(false), m_type(0) {
	m_isTimeBased = false;
	m_value = 0;
}

void Weapon::activate(const sf::Vector2f& pos) {
	if (m_isActive)
		return;
	m_isActive = true;
	m_obj = sf::RectangleShape(sf::Vector2f(10, -50));
	m_obj.setPosition(pos);
	m_obj.setFillColor(sf::Color::Green);
}

void Weapon::checkEnd() {
	if (m_obj.getSize().y < -WINDOW_HEIGHT + WALL_SIZE * 2) {
		m_isActive = false;
		m_obj.setSize(sf::Vector2f());
	}
	else if(m_isActive)
		m_obj.setSize(m_obj.getSize() + sf::Vector2f(0, -1));
}

void Weapon::draw(sf::RenderWindow& window) {
	if (m_isActive)
		window.draw(m_obj);
}