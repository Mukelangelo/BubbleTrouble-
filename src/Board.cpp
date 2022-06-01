#include "Board.h"


void Board::draw(sf::RenderWindow& window) 
{
	for (auto& wall : m_walls)
	{
		wall->draw(window);
	}
	for (auto& gift : m_gifts)
		gift->draw(window);
}

void Board::buildBackGround(b2World* world)
{
	for (auto i = 50.f; i <= WINDOW_WIDTH; i += WALL_SIZE / 2.f)
		m_walls.push_back(std::move(std::make_unique<Wall>(sf::Vector2f(i, 50.f), world)));
	for (auto i = 50.f; i <= WINDOW_WIDTH; i += WALL_SIZE / 2.f)
		m_walls.push_back(std::move(std::make_unique<Wall>(sf::Vector2f(i, WINDOW_HEIGHT - (WALL_SIZE/ 2.f)+10), world)));
	for (auto i = 50.f; i < WINDOW_HEIGHT; i += WALL_SIZE / 2.f)
		m_walls.push_back(std::move(std::make_unique<Wall>(sf::Vector2f(50.f, i), world)));
	for (auto i = 50.f; i < WINDOW_HEIGHT; i += WALL_SIZE / 2.f)
		m_walls.push_back(std::move(std::make_unique<Wall>(sf::Vector2f(WINDOW_WIDTH - (WALL_SIZE / 2.f), i), world)));

	buildBorder(world);
}

void Board::buildBorder(b2World* world)
{
	b2BodyDef bodyDef;
	b2PolygonShape groundBox;
	b2FixtureDef fixtureDef;

	bodyDef.type = b2_staticBody;
	bodyDef.position.Set(WALL_SIZE / 2.f, WINDOW_HEIGHT - WALL_SIZE * 1.5f);
	m_border.push_back(world->CreateBody(&bodyDef));

	auto size = m_walls[0]->getSize();
	groundBox.SetAsBox(size.x / 2.f, size.y / 2.f);

	fixtureDef.shape = &groundBox;
	fixtureDef.filter.categoryBits = WALL;
	fixtureDef.filter.maskBits = entity::BALL | entity::PLAYER;
	fixtureDef.filter.groupIndex = -1;

	m_border[0]->CreateFixture(&fixtureDef);

	bodyDef.position.Set(WINDOW_WIDTH - WALL_SIZE / 2.f, WINDOW_HEIGHT - WALL_SIZE * 1.5f);
	m_border.push_back(world->CreateBody(&bodyDef));

	fixtureDef.filter.groupIndex = -2;
	m_border[1]->CreateFixture(&fixtureDef);
}
//=======================================================================================
void Board::addGift(const sf::Vector2f& loc, b2World* world)
{
	m_gifts.push_back(std::move(std::make_unique<Gift>(Gift(loc, world, 1))));
}
//=======================================================================================
void Board::eraseGift(const sf::Sprite& sprite, b2World* world)
{
	for (auto gift = m_gifts.begin(); gift != m_gifts.end(); gift++)
	{
		if ((*gift)->getRectangle().getGlobalBounds().intersects(sprite.getGlobalBounds()))
		{
			world->DestroyBody(&(*gift)->getBody());
			m_gifts.erase(gift);
			break;
		}
	}
}
//=======================================================================================
void Board::updateGifts()
{
	for (auto& gift : m_gifts)
	{
		gift->updateGift();
	}
}
