#include "Board.h"


void Board::draw(sf::RenderWindow& window) 
{
	for (auto& wall : m_walls)
	{
		wall->draw(window);
	}
}

void Board::buildBackGround(b2World* world)
{
	for (auto i = 0.f; i <= WINDOW_HEIGHT; i += WALL_SIZE )
		m_walls.push_back(std::move(std::make_unique<Wall>(sf::Vector2f(0.f, i), world)));
	for (auto i = 0.f; i <= WINDOW_HEIGHT; i += WALL_SIZE)
		m_walls.push_back(std::move(std::make_unique<Wall>(sf::Vector2f(WINDOW_WIDTH, i), world)));
	for (auto i = WALL_SIZE * 2; i < WINDOW_WIDTH; i += WALL_SIZE)
		m_walls.push_back(std::move(std::make_unique<Wall>(sf::Vector2f(i, 0.f), world)));
	for (auto i = WALL_SIZE * 2; i < WINDOW_WIDTH; i += WALL_SIZE)
		m_walls.push_back(std::move(std::make_unique<Wall>(sf::Vector2f(i, WINDOW_HEIGHT), world)));
}
