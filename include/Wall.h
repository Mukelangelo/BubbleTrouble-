#pragma once
#include "StaticObject.h"

class Wall : public StaticObject 
{
public:
	Wall() = default;
	Wall(const sf::Vector2f& pos, b2World* world);

private:
	void initWall(const sf::Vector2f& loc);
	
	b2World* m_world;
	b2Body* m_body;
	b2Fixture* m_fixture;
};