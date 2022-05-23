#pragma once

#include "MovingObject.h"

class Ball : public MovingObject {
public:
	Ball() = default;
	Ball(const sf::Vector2f& loc, float radius, b2World* world);
	void initBall(const sf::Vector2f& loc, float radius, b2World* world);
	void updateBall();
	void draw(sf::RenderWindow& window);

private:
	float m_radius;
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2CircleShape m_dynamicCircle;
	b2FixtureDef m_fixtureDef;

	b2Vec2 m_position;
	float m_angle;
	sf::CircleShape m_circle;

};