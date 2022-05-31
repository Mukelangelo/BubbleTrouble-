#include "Wall.h"

Wall::Wall(const sf::Vector2f& pos, b2World* world)
	:m_world(world), m_size((*Resources::instance().getTexture(_game_objects::WALL_GO)).getSize())
{
	m_sprite = sf::Sprite(*Resources::instance().getTexture(_game_objects::WALL_GO));
	m_sprite.setOrigin(m_size / 2.f);
	//m_sprite.setScale(sf::Vector2f(1.05f, 1.05f));
	initWall(pos);
	m_sprite.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
	m_location = pos;
	
}


void Wall::initWall(const sf::Vector2f& loc)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(loc.x, loc.y);
	m_body = m_world->CreateBody(&bodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(m_size.x / 2.f - b2_polygonRadius, m_size.y / 2.f - b2_polygonRadius);

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &groundBox;
	fixtureDef.filter.categoryBits = WALL;
	fixtureDef.filter.maskBits = _entity::BALL | _entity::PLAYER ;

	m_fixture = m_body->CreateFixture(&fixtureDef);
}

sf::Vector2f Wall::getSize() const
{
	return m_size;
}