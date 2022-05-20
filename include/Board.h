#pragma once

#include <SFML/Graphics.hpp>
#include "macros.h"

class Board {
public:
	Board();
	void draw(sf::RenderWindow& window);

private:
	void buildBackGround();

	sf::RectangleShape m_background;
};