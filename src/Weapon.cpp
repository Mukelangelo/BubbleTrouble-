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
	m_obj.setOrigin(m_obj.getSize() / 2.f);
}

void Weapon::checkEnd() 
{
	if (m_obj.getSize().y < -WINDOW_HEIGHT + WALL_SIZE * 2) 
	{
		m_isActive = false;
		m_obj.setSize(sf::Vector2f());
		m_body->SetTransform(b2Vec2(0, WINDOW_HEIGHT), m_body->GetAngle());
	}
	else if (m_isActive)
	{
		m_obj.setSize(m_obj.getSize() + sf::Vector2f(0, -1));
		sf::Vector2f temp = m_obj.getPosition();
		m_body->SetTransform(b2Vec2(temp.x, temp.y + WALL_SIZE), m_body->GetAngle());
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
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0, 0);
	m_body = m_world->CreateBody(&bodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(WALL_SIZE / 200.f, (WINDOW_HEIGHT - WALL_SIZE) / 2.f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.filter.categoryBits = WEAPON;
	m_fixtureDef.filter.maskBits = BALL;

	m_fixture = m_body->CreateFixture(&fixtureDef);
}

void Weapon::forceEnd()
{
	m_isActive = false;
	m_obj.setSize(sf::Vector2f());
	m_body->SetTransform(b2Vec2(0, 0), m_body->GetAngle());
}