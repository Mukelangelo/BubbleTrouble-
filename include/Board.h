#pragma once

#include <SFML/Graphics.hpp>
#include "macros.h"

constexpr int WALL_SIZE = 100;

class Board {
public:
	Board();
	void draw(sf::RenderWindow& window);

private:
	void buildBackGround();

	sf::RectangleShape m_background;
};