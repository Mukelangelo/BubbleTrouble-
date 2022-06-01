#include "HookWeapon.h"
#include <iostream>

HookWeapon::HookWeapon(b2World* world) : m_shooting(false), m_type(0), m_world(world)
{
	m_isTimeBased = true;
	m_value = 1;
	initWeapon();
}

void HookWeapon::activate(const sf::Vector2f& pos)
{
	if (m_isActive)
		return;
	m_isActive = true;
	m_pos = pos;
	m_obj = sf::RectangleShape(sf::Vector2f(WALL_SIZE / 12.f, WINDOW_HEIGHT));
	m_obj.setOrigin(m_obj.getSize() / 2.f);
	m_obj.setFillColor(sf::Color::Green);
	b2Vec2 bodyPos = m_body->GetPosition();
	m_obj.setPosition(sf::Vector2f(bodyPos.x, bodyPos.y));
}

void HookWeapon::checkEnd()
{
	b2Vec2 position = m_body->GetPosition();
	if (position.y < 5 * WALL_SIZE)
	{
		m_isActive = false;
		count_down -= m_Timer.getElapsedTime().asSeconds();
		if (count_down < 0)
		{
			m_obj.setSize(sf::Vector2f());
			m_body->SetTransform(b2Vec2(0, 0), m_body->GetAngle());
			count_down = 3.f;
		}
		else
		{
			m_obj.setSize(sf::Vector2f(m_pos.x, WINDOW_HEIGHT - WALL_SIZE));
			m_body->SetTransform(b2Vec2(m_pos.x, WINDOW_HEIGHT), m_body->GetAngle());
		}
		m_Timer.restart();
	}
	else if (m_isActive)
	{
		m_body->SetTransform(b2Vec2(m_pos.x, 1.5f * m_pos.y--), m_body->GetAngle());
		m_obj.setPosition(sf::Vector2f(position.x, position.y));
	}
}

void HookWeapon::draw(sf::RenderWindow& window)
{
	if (m_isActive)
		window.draw(m_obj);
}

void HookWeapon::initWeapon()
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(0, 0);
	m_body = m_world->CreateBody(&bodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox((WALL_SIZE / 12.f) / 2.f, (WINDOW_HEIGHT) / 2.f);

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.filter.categoryBits = WEAPON;
	m_fixtureDef.filter.maskBits = BALL;

	m_fixture = m_body->CreateFixture(&fixtureDef);
}

void HookWeapon::forceEnd()
{
	m_isActive = false;
	m_obj.setSize(sf::Vector2f());
	m_body->SetTransform(b2Vec2(0, 0), m_body->GetAngle());
}