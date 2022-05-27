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
	bool movementManger(sf::Time& deltaTime, sf::Clock& clock);
	bool checkBoundries();
	void setUpGame();
	void checkSplit();

	Board m_board;
	Player m_player;
	std::vector<Ball> m_balls;	// later to be vector ot smth

	b2Vec2 m_garvity = b2Vec2(0.f, 10.0f);
	std::unique_ptr<b2World> m_world;
	/*
	// floor
	b2BodyDef m_groundBodyDef;
	b2Body* m_groundBody;
	b2PolygonShape m_groundBox;
	// right wall
	b2BodyDef m_rightWallBodyDef;
	b2Body* m_rightWallBody;
	b2PolygonShape m_rightWallBox;
	// left wall
	b2BodyDef m_leftWallBodyDef;
	b2Body* m_leftWallBody;
	b2PolygonShape m_leftWallBox;
	*/
	float m_timeStep = 1.0f / 60.0f;
	int32 m_velocityIterations = 6;
	int32 m_positionIterations = 2;
	Caption m_caption;

	ContactListener m_cl;

	b2Vec2 m_leftVelocity = b2Vec2(-15.f, 1.f);
	b2Vec2 m_rightVelocity = b2Vec2(15.f, 1.f);
};