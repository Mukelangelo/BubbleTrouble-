#pragma once

#include "Power.h"

class Weapon : public Power {
public:
	Weapon() = default;
	Weapon(b2World* world);

	void checkEnd();
	void forceEnd();
	void activate(const sf::Vector2f& pos);
	void draw(sf::RenderWindow& window);

	~Weapon() = default;

private:
	void initWeapon();

	int m_type;
	bool m_shooting;

	b2Body* m_body;
	b2FixtureDef m_fixtureDef;

	b2World* m_world;
	b2Fixture* m_fixture;
};