#include "Ball.h"
#include <iostream>

Ball::Ball(const sf::Vector2f& loc, float radius, b2World* world) : m_radius(radius)
{
	initBall(loc, radius, world);
	
	m_position = m_body->GetPosition();
	m_angle = m_body->GetAngle();

	m_circle = sf::CircleShape(radius);
	m_circle.setPosition(loc);
	m_circle.setTexture(&(* Resources::instance().getTexture(_game_objects::BALL_GO)));
	m_circle.setOrigin(radius, radius);
	
}

void Ball::initBall(const sf::Vector2f& loc, float radius, b2World* world) 
{
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(loc.x, loc.y);
	m_bodyDef.linearVelocity = b2Vec2(-10.f, 0.f);
	//m_bodyDef.linearVelocity = b2Vec2(0.f, 0.f);
	m_body = world->CreateBody(&m_bodyDef);

	m_dynamicCircle.m_p.Set(1.f, 1.f);
	m_dynamicCircle.m_radius = radius;

	m_fixtureDef.shape = &m_dynamicCircle;
	m_fixtureDef.density = 1.f;
	m_fixtureDef.friction = 0.f;
	m_fixtureDef.restitution = 1.f;
	m_fixtureDef.filter.categoryBits = BALL;
	m_fixtureDef.filter.maskBits = WEAPON | WALL | PLAYER;
	m_body->CreateFixture(&m_fixtureDef);

}

void Ball::updateBall() 
{
	for (auto edge = m_body->GetContactList(); edge; edge = edge->next)
	{
		auto entity = edge->contact->GetFixtureA()->GetFilterData().categoryBits;
	}

	m_position = m_body->GetPosition();
	m_angle = m_body->GetAngle();

	m_circle.setPosition(m_position.x, m_position.y);
	m_sprite.setRotation(m_angle);

}

void Ball::draw(sf::RenderWindow& window) 
{
	window.draw(m_circle);
}

bool Ball::getPopStatus()
{
	return m_pop;
}