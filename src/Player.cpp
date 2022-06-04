#include "Player.h"


Player::Player(const sf::Vector2f& pos, b2World* world, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed)
	: m_world(world), m_size((* Resources::instance().getTexture(_game_objects::BATMAN_STAND)).getSize()), m_animation(texture, imageCount, switchTime)
{
	initPlayer(pos);

	m_speed = speed;
	m_row = 0;
	m_faceRight = true;
	m_character.setSize(sf::Vector2f(50.0f, 100.0f));
	m_character.setPosition(sf::Vector2f(300.0f, 300.0f));
	m_character.setTexture(texture);
	m_character.setOrigin(m_size / 2.f);

	m_lastLoc = m_location = pos;
	m_speedPerSecond = m_sprite.getScale().x * 200;
	m_powers.push_back(std::make_unique<Weapon>(m_world));
	
	m_character.setPosition(sf::Vector2f(m_body->GetPosition().x, m_body->GetPosition().y));
}

void Player::draw(sf::RenderWindow& window) 
{
	for (auto& pow : m_powers) 
	{
		pow->draw(window);
	}
	//window.draw(m_sprite);
	window.draw(m_character);
}

void Player::move(bool isBlocked, std::pair<sf::Vector2f, bool> input, float deltaTime)
{
	setDirection(input.first);
	DirectionImg(input.first.x, deltaTime);
	if (input.second)
	{
		shoot();
		SetStandingImage(1);
	}
	m_location = m_character.getPosition();
	b2Vec2 pos = m_body->GetPosition();

	(isBlocked) ? m_body->SetTransform(b2Vec2(m_lastLoc.x, m_lastLoc.y), m_body->GetAngle()) :
				  m_body->SetTransform(b2Vec2(pos.x + m_direction.x, pos.y), m_body->GetAngle());

	m_character.setPosition(pos.x, pos.y);
	m_location = m_character.getPosition();
}

void Player::shoot() 
{
	m_powers[0]->activate(m_character.getPosition()); // need to center more efficintly
	
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

void Player::ballHit()
{
	m_powers[0]->forceEnd();
}

void Player::DirectionImg(int dir, float deltaTime)
{
	if (dir == 1)
	{
		m_faceRight = false;
		sf::Texture texture;
		texture.loadFromFile("batman-right-flow.png");
		Animation animation(&texture, sf::Vector2u(4, 1), 0.2f);
		m_character.setTextureRect(animation.uvRect);
		m_animation.Update(m_row, deltaTime, m_faceRight);
		m_character.setTextureRect(m_animation.uvRect);
	}
	else if(dir == -1)
	{
		m_faceRight = true;
		sf::Texture texture;
		texture.loadFromFile("batman-right-flow.png");
		Animation animation(&texture, sf::Vector2u(4, 1), 0.2f);
		m_character.setTextureRect(animation.uvRect);
		m_animation.Update(m_row, deltaTime, m_faceRight);
		m_character.setTextureRect(m_animation.uvRect);
	}
}

void Player::SetStandingImage(int image)
{
	if (image == 0)
	{
		//sf::Texture texture;
		//texture = *Resources::instance().getTexture(_game_objects::BATMAN_STAND);
		//Animation animation(&texture, sf::Vector2u(1, 1), 1.0f);
		//m_animation.Update(m_row, 1.0f, m_faceRight);
		//m_character.setTextureRect(animation.uvRect);
		//m_character.setTexture(Resources::instance().getTexture(_game_objects::BATMAN_STAND));
	}
	else if (image == 1)
	{
		/*sf::Texture texture;
		texture = *Resources::instance().getTexture(_game_objects::BATMAN_SHOT);
		Animation animation(&texture, sf::Vector2u(1, 1), 1.0f);
		m_character.setTextureRect(animation.uvRect);*/
		//m_character.setTexture(Resources::instance().getTexture(_game_objects::BATMAN_SHOT));
	}
	
}

void Player::setLocation(const sf::Vector2f& loc)
{
	GameObject::setLocation(loc);
	m_body->SetTransform(b2Vec2(loc.x, loc.y), m_body->GetAngle());
}