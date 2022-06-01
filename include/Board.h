#pragma once

#include "macros.h"
#include <iostream>
#include "Wall.h"
#include "Gift.h"

class Board {
public:
	Board() = default;
	void buildBackGround(b2World* world);
	void addGift(const sf::Vector2f& loc, b2World* world);
	void eraseGift(const sf::Sprite& sprite, b2World* world);
	void draw(sf::RenderWindow& window);
	void updateGifts();
private:
	std::vector<std::unique_ptr<Wall>> m_walls;
	std::vector<std::unique_ptr<Gift>> m_gifts;
	std::vector<b2Body*> m_border;

	void buildBorder(b2World* world);
};