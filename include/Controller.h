#pragma once
#include "Board.h"
#include "Player.h"
#include "Ball.h"
#include "Wall.h"
#include "Caption.h"
#include "ContactListener.h"

class Controller {
public:
	// default c-stor
	Controller();
	// run the game
	void run(sf::RenderWindow& window);

private:
	bool eventHandler(sf::Event& event, sf::RenderWindow& window);
	bool movementManger();
	void checkSplit();
	bool pauseMenu(sf::RenderWindow& window);
	std::pair<sf::Vector2f, bool> getInput();
	sf::Vector2f directionInput();
	bool shootingInput();

	Board m_board;
	Player m_player;
	std::vector<std::unique_ptr<Ball>> m_balls;	// later to be vector ot smth

	b2Vec2 m_garvity = b2Vec2(0.f, 10.0f);
	std::unique_ptr<b2World> m_world;

	float m_timeStep = 1.0f / 60.0f;
	int32 m_velocityIterations = 6;
	int32 m_positionIterations = 2;
	Caption m_caption;

	ContactListener m_cl;

	b2Vec2 m_leftVelocity = b2Vec2(-40.f, 1.f);
	b2Vec2 m_rightVelocity = b2Vec2(40.f, 1.f);
};