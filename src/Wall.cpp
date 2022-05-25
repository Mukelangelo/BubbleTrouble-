#include "Wall.h"

Wall::Wall(const sf::Vector2f& pos, b2World* world)
	:m_world(world)
{
	m_sprite = sf::Sprite(*Resources::instance().getTexture(_game_objects::WALL_GO));
	m_sprite.setPosition(pos);
	m_sprite.setOrigin((sf::Vector2f)(*Resources::instance().getTexture(_game_objects::WALL_GO)).getSize() / 2.f);
	m_sprite.setScale(sf::Vector2f(2.f, 2.f));
	m_location = pos;
	initWall(pos);
}


void Wall::initWall(const sf::Vector2f& loc)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(loc.x, loc.y);
	m_body = m_world->CreateBody(&bodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(WALL_SIZE/2.f , WALL_SIZE/2.f);

	b2FixtureDef fixtureDef;

	fixtureDef.shape = &groundBox;
	fixtureDef.filter.categoryBits = WALL;
	//fixtureDef.filter.maskBits = _entity::BALL | _entity::PLAYER;

	m_fixture = m_body->CreateFixture(&fixtureDef);
}