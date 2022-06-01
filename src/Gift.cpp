#include "Gift.h"
#include <iostream>

//=======================================================================================
Gift::Gift(const sf::Vector2f& loc, b2World* world, const int& value)
	:m_value(value)
{
	m_gift.setSize(sf::Vector2f(25.f, 25.f));
	switch (value)
	{
		case gift::NORMAL_WEAPON : m_gift.setFillColor(sf::Color::Green); break;
		case gift::HOOK_WEAPON: m_gift.setTexture(&(*Resources::instance().getTexture(gameObjects::GIFT_GO))); break;
	}
	
	m_bodyDef.type = b2_dynamicBody;
	m_bodyDef.position.Set(loc.x, loc.y);
	m_bodyDef.linearVelocity = b2Vec2(0.f, 5.f);
	
	m_bodyDef.gravityScale = 1;
	m_body = world->CreateBody(&m_bodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(m_gift.getSize().x , m_gift.getSize().y );

	b2FixtureDef fixtureDef;
	fixtureDef.shape = &groundBox;
	fixtureDef.density = 0.5;
	
	fixtureDef.filter.categoryBits = entity::GIFT;
	fixtureDef.filter.maskBits = entity::PLAYER | entity::WALL;
	m_body->CreateFixture(&fixtureDef);

	m_gift.setPosition(loc);
}
//=======================================================================================
void Gift::updateGift()
{
	auto position = m_body->GetPosition();
	m_gift.setPosition(position.x, position.y);
	m_location = m_gift.getPosition();
}
//=======================================================================================
void Gift::draw(sf::RenderWindow& window)
{
	window.draw(m_gift);
}
//=======================================================================================
int Gift::getValue() const
{
	return m_value;
}
//=======================================================================================
b2Body& Gift::getBody() const
{
	return *m_body;
}
sf::RectangleShape Gift::getRectangle() const
{
	return m_gift;
}