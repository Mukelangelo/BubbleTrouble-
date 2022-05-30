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
	m_pos = pos;
	m_obj = sf::RectangleShape(sf::Vector2f(WALL_SIZE / 8.f, WINDOW_HEIGHT));
	m_obj.setOrigin(m_obj.getSize() / 2.f);
	m_obj.setFillColor(sf::Color::Magenta);
	b2Vec2 bodyPos = m_body->GetPosition();
	m_obj.setPosition(sf::Vector2f(bodyPos.x, bodyPos.y));
}

void Weapon::checkEnd() 
{
	b2Vec2 position = m_body->GetPosition();
	if (position.y < 3 * WALL_SIZE)
	{
		
		m_isActive = false;
		m_obj.setSize(sf::Vector2f());
		m_body->SetTransform(b2Vec2(0, WINDOW_HEIGHT), m_body->GetAngle());
	}
	else if (m_isActive)
	{
		m_body->SetTransform(b2Vec2(m_pos.x, 1.5f * m_pos.y--), m_body->GetAngle());
		m_obj.setPosition(sf::Vector2f(position.x, position.y));
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
	groundBox.SetAsBox((WALL_SIZE / 8.f) / 2.f, (WINDOW_HEIGHT) / 2.f);

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