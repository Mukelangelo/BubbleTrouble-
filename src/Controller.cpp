#include "Controller.h"
#include <iostream>

Controller::Controller()
	: m_board(), m_player(), m_caption()
{
	m_world = std::make_unique<b2World>(m_garvity);
	m_board.buildBackGround(m_world.get());
	m_player = Player(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 1.5 * WALL_SIZE), m_world.get());

	m_balls.push_back(std::move(std::make_unique<Ball>(Ball(sf::Vector2f(WINDOW_WIDTH / 3, 2 * WALL_SIZE), _ball_radius::MEGA_BIG, m_world.get(), m_rightVelocity))));
	m_balls.push_back(std::move(std::make_unique<Ball>(Ball(sf::Vector2f(WINDOW_WIDTH / 3, 2 * WALL_SIZE), _ball_radius::BIG, m_world.get(), m_rightVelocity))));
	m_balls.push_back(std::move(std::make_unique<Ball>(Ball(sf::Vector2f(WINDOW_WIDTH / 3, 2 * WALL_SIZE), _ball_radius::MEDIUM, m_world.get(), m_rightVelocity))));
	m_balls.push_back(std::move(std::make_unique<Ball>(Ball(sf::Vector2f(WINDOW_WIDTH / 3, 2 * WALL_SIZE), _ball_radius::SMALL, m_world.get(), m_rightVelocity))));

	m_world->SetContactListener(&m_cl);
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
			ball->updateBall();
		}
		checkSplit();

		window.clear(sf::Color::White);
		m_board.draw(window);
		m_player.draw(window);
		for (auto& ball : m_balls)
		{
			ball->draw(window);
		}
		m_caption.draw(window);
		window.display();
		
		
		if (m_cl.getPlayerHit())
		{
			m_caption.removeLive();
			m_caption.resetTime();
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
		default:
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
				m_player.SetStandingImage(1);
			}
		}
		if (event.type == sf::Event::KeyReleased)
		{
			m_player.SetStandingImage(0);
		}
	}
	return true;
}

bool Controller::movementManger(sf::Time& deltaTime, sf::Clock& clock) 
{
	m_player.setLastLoc(); // set last location as current location
	deltaTime = clock.restart();
	//if (m_player.handleCollision())
	//{
	//	//checkBoundries();
	//	return false;
	//}
	/*
	if (!checkBoundries())
		return false;
		*/
	m_player.move(deltaTime);
	
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

void Controller::checkSplit()
{
	int index = -1;
	if (m_cl.getSplit(index))
	{
		for (auto it = m_balls.begin(); it < m_balls.end(); it++)
		{
			if ((*it)->getId() == index)
			{
				m_player.ballHit();
				auto radius = (*it)->getRadius() / 2;
				auto loc = (*it)->getLocation();
				m_world->DestroyBody(&(*it)->getBody());
				m_balls.erase(it);	// split here
				if (radius > _ball_radius::SMALL)
				{
					m_balls.push_back(std::move(std::make_unique<Ball>(Ball(loc + sf::Vector2f(radius / 2, 0), radius, m_world.get(), m_rightVelocity))));
					m_balls.push_back(std::move(std::make_unique<Ball>(Ball(loc - sf::Vector2f(radius / 2, 0), radius, m_world.get(), m_leftVelocity))));
				}
				return;
			}
		}
	}
}
