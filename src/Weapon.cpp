#include "Weapon.h"
#include <iostream>

Weapon::Weapon(b2World* world) : m_shooting(false), m_type(0), m_world(world)
{
	m_isTimeBased = false;
	m_value = 0;
	initWeapon();
}

void Weapon::activate(const sf::Vector2f& pos)
{
	if (m_isActive)
		return;
	m_isActive = true;
	m_obj = sf::RectangleShape(sf::Vector2f(SHOT_WIDTH, SHOT_HEIGHT));
	m_obj.setPosition(pos);
	m_obj.setFillColor(sf::Color::Magenta);
	//

}

void Weapon::checkEnd() 
{
	if (m_obj.getSize().y < -WINDOW_HEIGHT + WALL_SIZE * 2) 
	{
		m_isActive = false;
		m_obj.setSize(sf::Vector2f());
	}
	else if (m_isActive)
	{
		m_obj.setSize(m_obj.getSize() + sf::Vector2f(0, -1));
	}
}

void Weapon::draw(sf::RenderWindow& window) 
{
	if (m_isActive)
		window.draw(m_obj);
}

void Weapon::initWeapon()
{
	b2BodyDef bodyDef;
	bodyDef.position.Set(0, WINDOW_HEIGHT);
	m_body = m_world->CreateBody(&bodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(WALL_SIZE / 4.f, (WINDOW_HEIGHT - 2 * WALL_SIZE));

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.filter.categoryBits = WEAPON;
	m_fixtureDef.filter.maskBits = BALL;

	m_fixture = m_body->CreateFixture(&fixtureDef);
}