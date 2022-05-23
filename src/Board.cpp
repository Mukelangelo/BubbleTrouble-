#include "Board.h"

Board::Board() 
{
	buildBackGround();
}

void Board::draw(sf::RenderWindow& window) 
{
	window.draw(m_background);
}

void Board::buildBackGround() 
{
	m_background = sf::RectangleShape(sf::Vector2f(WINDOW_WIDTH - WALL_SIZE * 2, WINDOW_HEIGHT - WALL_SIZE * 2));
	m_background.setPosition(sf::Vector2f(WALL_SIZE, WALL_SIZE));
	m_background.setOutlineColor(sf::Color(128, 128, 128));
	m_background.setFillColor(sf::Color::White);
	m_background.setOutlineThickness(WALL_SIZE);
}