#pragma once

#include "MovingObject.h"

static int id = 0;

class Ball : public MovingObject {
public:
	Ball() = default;
	Ball(const sf::Vector2f& loc, float radius, b2World* world, const b2Vec2& velocity);
	void updateBall();
	void draw(sf::RenderWindow& window);
	bool getPopStatus() const;
	int getId() const;
	float getRadius() const;
	b2Body& getBody() const;

protected:
	virtual void DirectionImg(int dir) {};

private:
	void initBall(const sf::Vector2f& loc, float radius, b2World* world, const b2Vec2& velocity);
	float getGravityScale() const;

	float m_radius;
	b2BodyDef m_bodyDef;
	b2Body* m_body;
	b2CircleShape m_dynamicCircle;
	b2FixtureDef m_fixtureDef;

	b2Vec2 m_position;
	float m_angle;
	sf::CircleShape m_circle;

	bool m_pop = false;
};