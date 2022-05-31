#pragma once

#include <SFML/Graphics.hpp>
#include "macros.h"
#include "Wall.h"

class Board {
public:
	Board() = default;
	void buildBackGround(b2World* world);
	void draw(sf::RenderWindow& window);

private:
	std::vector<std::unique_ptr<Wall>> m_walls;
	std::vector<b2Body*> m_border;

	void buildBorder(b2World* world);
};