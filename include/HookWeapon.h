#pragma once
#include "Power.h"

class HookWeapon : Power {
public:
	HookWeapon() = default;
	HookWeapon(b2World * world);

	void checkEnd();
	void forceEnd();
	void activate(const sf::Vector2f & pos);
	void draw(sf::RenderWindow & window);

	~HookWeapon() = default;

private:
	void initWeapon();

	int m_type;
	bool m_shooting;

	b2Body* m_body;
	b2FixtureDef m_fixtureDef;

	b2World* m_world;
	b2Fixture* m_fixture;

	float count_down = 3.f;
	sf::Clock m_Timer;

	sf::Vector2f m_pos;
};