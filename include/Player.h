#pragma once

#include "MovingObject.h"
#include "Weapon.h"

class Player : public MovingObject{
public:
	Player() = default;
	Player(const sf::Vector2f& pos, b2World* world);

	void move(sf::Time deltaTime);
	void shoot();
	void handlePowers();
	void ballHit();

	void draw(sf::RenderWindow& window);
	bool handleCollision();

protected:
	virtual void DirectionImg(int dir) override;

private:
	void initPlayer(const sf::Vector2f& loc);

	int m_lives = 3;
	std::vector< std::unique_ptr<Power> > m_powers; // maybe shared?
	b2World* m_world;
	b2Body* m_body;
	b2Fixture* m_fixture;
};