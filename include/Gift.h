#pragma once
#include "StaticObject.h"

class Gift : public StaticObject {
public:
	Gift() = default;
	Gift(const sf::Vector2f& loc, b2World* world, const int& value);
	void updateGift();
	void draw(sf::RenderWindow& window);
	int getValue() const;
	sf::RectangleShape getRectangle() const;
	b2Body& getBody() const;

private:
	int m_value;
	sf::RectangleShape m_gift;
	b2Body* m_body;
	b2BodyDef m_bodyDef;
	b2Fixture* m_fixture;
};