#include "Player.h"

Player::Player(const sf::Vector2f& pos, b2World* world)
	: m_world(world)
{
	m_sprite = sf::Sprite(*Resources::instance().getTexture(0));
	m_sprite.setPosition(pos);
	m_sprite.setOrigin((sf::Vector2f)(* Resources::instance().getTexture(0)).getSize() / 2.f);
	m_lastLoc = m_location = pos;
	m_speedPerSecond = m_sprite.getScale().x * 200;
	m_powers.push_back(std::make_unique<Weapon>(m_world));
	initPlayer(pos);
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
	m_sprite.move(m_direction * m_speedPerSecond * deltaTime.asSeconds());
	m_location = m_sprite.getPosition();
	m_body->SetTransform(b2Vec2(m_location.x, m_location.y), m_body->GetAngle());
}

void Player::shoot() 
{
	m_powers[0]->activate(m_sprite.getPosition() + sf::Vector2f(0, WALL_SIZE / 4)); // need to center more efficintly
	
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
	groundBox.SetAsBox(WALL_SIZE / 4.f, WALL_SIZE / 2.f);

	b2FixtureDef fixtureDef;
	
	fixtureDef.shape = &groundBox;
	fixtureDef.filter.categoryBits = PLAYER;
	m_fixtureDef.filter.maskBits = BALL;

	m_fixture = m_body->CreateFixture(&fixtureDef);
}

bool Player::checkBallHit()
{
	for (auto edge = m_body->GetContactList(); edge; edge = edge->next)
	{
		auto entity = edge->contact->GetFixtureB()->GetFilterData().categoryBits;
		if (entity == BALL)
		{
			return true;
		}
	}
	return false;
}