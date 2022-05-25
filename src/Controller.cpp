#include "Controller.h"
#include <iostream>

Controller::Controller()
	: m_board(), m_player(), m_caption()
{
	setUpGame();
	m_player = Player(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 1.5 * WALL_SIZE), m_world.get());
	m_balls.push_back(Ball(sf::Vector2f(WINDOW_WIDTH / 2, 2 * WALL_SIZE), 50, m_world.get()));
	m_balls.push_back(Ball(sf::Vector2f(WINDOW_WIDTH / 3, 2 * WALL_SIZE), 100, m_world.get()));
}

void Controller::run(sf::RenderWindow& window) 
{
	sf::Event event;
	const sf::Time timerLimit = sf::seconds(0.1f);
	sf::Clock clock;
	sf::Time deltaTimePlayer;

	m_caption.updateLevel();
	m_caption.updateTime(STAGE_TIME);
	m_caption.updateLives();

	bool played_countdown = false;
	
	while (window.isOpen()) 
	{
		m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);
		for (auto& ball : m_balls) 
		{
			ball.updateBall();
		}

		window.clear(sf::Color::White);
		m_board.draw(window);
		m_player.draw(window);
		for (auto& ball : m_balls)
		{
			ball.draw(window);
		}
		m_caption.draw(window);
		window.display();
		
		if (m_player.checkBallHit())
		{
			m_caption.removeLive();
		}

		//if (m_caption.getTime() <= 4 && !played_countdown)
		//{ //when timer in on the last 5 seconds , a coundown sound is played
		//	Resources::instance().playSound(countdown_sound);
		//	played_countdown = true;
		//}

		if (m_caption.getTime() <= 0) // means game over
		{
			m_caption.printMessege("NOOB! , you lost :( shame on you", window);
			return;
		}

		if (!eventHandler(event, window))
		{
			return;
		}
		
		if (clock.getElapsedTime() >= timerLimit)
		{
			clock.restart();
		}

		switch (event.type)
		{
		case sf::Event::KeyPressed:
			movementManger(deltaTimePlayer, clock);
			break;
		}
		m_player.handlePowers();
	}
}

bool Controller::eventHandler(sf::Event& event, sf::RenderWindow& window) 
{
	while (window.pollEvent(event)) 
	{
		if ((event.type == sf::Event::Closed) ||
			((event.type == sf::Event::KeyPressed) && 
		    (event.key.code == sf::Keyboard::Escape))) 
		{
			return false;
		}

		if (event.type == sf::Event::KeyPressed) 
		{
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
			{
				m_player.setDirection(sf::Keyboard::Right);
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
			{
				m_player.setDirection(sf::Keyboard::Left);
			}

			else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
			{
				m_player.shoot();
			}
		}
	}
	return true;
}

bool Controller::movementManger(sf::Time& deltaTime, sf::Clock& clock) 
{
	m_player.setLastLoc(); // set last location as current location
	deltaTime = clock.restart();
	if (!checkBoundries())
	{
		return false;
	}
	m_player.move(deltaTime);
	
	//manage collision here (?)

	return true;
}
bool Controller::checkBoundries() 
{
	auto temp = m_player.getLocation();
	if (temp.x < WALL_SIZE) 
	{
		m_player.setLocation(sf::Vector2f(WALL_SIZE, temp.y));
		return false;
	}
	if (temp.x + WALL_SIZE > WINDOW_WIDTH - WALL_SIZE) 
	{
		m_player.setLocation(sf::Vector2f(WINDOW_WIDTH - 2 * WALL_SIZE, temp.y));
		return false;
	}

	return true;
}

void Controller::setUpGame() 
{
	m_world = std::make_unique<b2World>(m_garvity);
	m_groundBodyDef.position.Set(0.0f, WINDOW_HEIGHT);
	m_groundBody = m_world->CreateBody(&m_groundBodyDef);
	m_groundBox.SetAsBox(WINDOW_WIDTH, WALL_SIZE);
	m_groundBody->CreateFixture(&m_groundBox, 0.0f);

	m_rightWallBodyDef.position.Set(WINDOW_WIDTH, 0.0f);
	m_rightWallBody = m_world->CreateBody(&m_rightWallBodyDef);
	m_rightWallBox.SetAsBox(WALL_SIZE, WINDOW_HEIGHT);
	m_rightWallBody->CreateFixture(&m_rightWallBox, 0.0f);

	m_leftWallBodyDef.position.Set(0.0f, 0.0f);
	m_leftWallBody = m_world->CreateBody(&m_leftWallBodyDef);
	m_leftWallBox.SetAsBox(0.0f, WINDOW_HEIGHT);
	m_leftWallBody->CreateFixture(&m_leftWallBox, 0.0f);
}