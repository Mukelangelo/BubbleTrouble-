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
	for (auto i = 50.f; i <= WINDOW_WIDTH; i += WALL_SIZE / 2.f)
		m_walls.push_back(std::move(std::make_unique<Wall>(sf::Vector2f(i, 50.f), world)));
	for (auto i = 50.f; i <= WINDOW_WIDTH; i += WALL_SIZE / 2.f)
		m_walls.push_back(std::move(std::make_unique<Wall>(sf::Vector2f(i, WINDOW_HEIGHT - (WALL_SIZE/ 2.f)), world)));
	for (auto i = 50.f; i < WINDOW_HEIGHT; i += WALL_SIZE / 2.f)
		m_walls.push_back(std::move(std::make_unique<Wall>(sf::Vector2f(50.f, i), world)));
	for (auto i = 50.f; i < WINDOW_HEIGHT; i += WALL_SIZE / 2.f)
		m_walls.push_back(std::move(std::make_unique<Wall>(sf::Vector2f(WINDOW_WIDTH - (WALL_SIZE / 2.f), i), world)));
}
