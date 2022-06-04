#pragma once

#include "MovingObject.h"
#include "Weapon.h"
#include "Animation.h"

class Player : public MovingObject
{
public:
	Player() = default;
	Player(const sf::Vector2f& pos, b2World* world, sf::Texture* texture, sf::Vector2u imageCount, float switchTime, float speed);

	void move(bool isBlocked, std::pair<sf::Vector2f, bool> input, float deltaTime);
	void shoot();
	void handlePowers();
	void ballHit();
	void SetStandingImage(int image);

	void draw(sf::RenderWindow& window);
	void setLocation(const sf::Vector2f& loc);

protected:
	virtual void DirectionImg(int dir, float deltaTime) override;
	
private:
	void initPlayer(const sf::Vector2f& loc);

	int m_lives = 3;
	std::vector<std::unique_ptr<Power>> m_powers; // maybe shared?
	b2World* m_world;
	b2Body* m_body;
	b2Fixture* m_fixture;
	sf::Vector2f m_size;
	
	sf::RectangleShape m_character;
	Animation m_animation;
	unsigned int m_row = 0;
	float m_speed = 0.0f;
	bool m_faceRight = true;
};