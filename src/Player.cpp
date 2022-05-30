#include "Player.h"

Player::Player(const sf::Vector2f& pos, b2World* world)
	: m_world(world), m_size((* Resources::instance().getTexture(_game_objects::BATMAN_STAND)).getSize())
{
	m_sprite = sf::Sprite(*Resources::instance().getTexture(_game_objects::BATMAN_STAND));
	
	m_sprite.setOrigin(m_size / 2.f);
	m_lastLoc = m_location = pos;
	m_speedPerSecond = m_sprite.getScale().x * 200;
	m_powers.push_back(std::make_unique<Weapon>(m_world));
	initPlayer(pos);
	m_sprite.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
}

void Player::draw(sf::RenderWindow& window) 
{
	for (auto& pow : m_powers) 
	{
		pow->draw(window);
	}
	window.draw(m_sprite);
}

void Player::move(sf::Time deltaTime)
{
	// m_sprite.move(m_direction * m_speedPerSecond * deltaTime.asSeconds());
	m_location = m_sprite.getPosition();
	b2Vec2 pos = m_body->GetPosition();
	m_body->SetTransform(b2Vec2(pos.x + m_direction.x, pos.y), m_body->GetAngle());
	m_sprite.setPosition(pos.x, pos.y);
	m_location = m_sprite.getPosition();
}

void Player::shoot() 
{
	m_powers[0]->activate(m_sprite.getPosition()); // need to center more efficintly
	
}

void Player::handlePowers() 
{
	for (auto& pow : m_powers) 
	{
		pow->checkEnd();
	}
}

void Player::initPlayer(const sf::Vector2f& loc)
{
	b2BodyDef bodyDef;
	bodyDef.type = b2_dynamicBody;
	bodyDef.position.Set(loc.x, loc.y);
	m_body = m_world->CreateBody(&bodyDef);

	b2PolygonShape groundBox;
	groundBox.SetAsBox(m_size.x / 2.f, m_size.y / 2.f);

	b2FixtureDef fixtureDef;
	
	fixtureDef.shape = &groundBox;
	fixtureDef.filter.categoryBits = _entity::PLAYER;
	fixtureDef.filter.maskBits = _entity::BALL | _entity::WALL;

	m_fixture = m_body->CreateFixture(&fixtureDef);
}

bool Player::handleCollision()
{
	for (auto edge = m_body->GetContactList(); edge; edge = edge->next)
	{
		auto entityA = edge->contact->GetFixtureA()->GetFilterData().categoryBits;
		auto entityB = edge->contact->GetFixtureB()->GetFilterData().categoryBits;
		if (entityA == _entity::BALL)
			return true;

		//if (entityA == _entity::WALL || entityB == _entity::WALL)
		//	return true;
	}
	return false;
}

void Player::ballHit()
{
	m_powers[0]->forceEnd();
}

void Player::DirectionImg(int dir)
{
	if (dir == 1)
	{
		m_sprite.setTexture(*Resources::instance().getTexture(_game_objects::BATMAN_WALK_RIGHT));
	}
	else if(dir == 0)
	{
		m_sprite.setTexture(*Resources::instance().getTexture(_game_objects::BATMAN_WALK_LEFT));
	}
}

void Player::SetStandingImage(int image)
{
	if (image == 0)
	{
		m_sprite.setTexture(*Resources::instance().getTexture(_game_objects::BATMAN_STAND));
	}
	else if (image == 1)
	{
		m_sprite.setTexture(*Resources::instance().getTexture(_game_objects::BATMAN_SHOT));
	}
	
}

void Player::setLocation(const sf::Vector2f& loc)
{
	GameObject::setLocation(loc);
	m_body->SetTransform(b2Vec2(loc.x, loc.y), m_body->GetAngle());
}