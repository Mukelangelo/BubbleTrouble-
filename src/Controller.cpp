#include "Controller.h"

#include <iostream>

Controller::Controller()
	: m_board(), m_player(), m_caption()
{
	restartLvl();
}

void Controller::run(sf::RenderWindow& window) 
{
	float deltaTime = 0.0f;
	sf::Clock clock2;

	sf::Event event;

	m_caption.updateLevel();
	m_caption.updateLives();

	bool played_countdown = false;
	
	while (window.isOpen()) 
	{
		deltaTime = clock2.restart().asSeconds();


		m_world->Step(m_timeStep, m_velocityIterations, m_positionIterations);
		for (auto& ball : m_balls) 
		{
			ball->updateBall();
		}
		checkSplit();

		window.clear(sf::Color::White);
		
		//m_player.Update(deltaTime);

		m_player.draw(window);
		m_board.draw(window);
		m_caption.draw(window);
		for (auto& ball : m_balls)
		{
			ball->draw(window);
		}
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

		if (!eventHandler(event, window))
		{
			return;
		}
		movementManger(deltaTime);
		m_player.handlePowers();
		if (m_balls.empty())
		{
			m_caption.printMessege("YAY! , you won :) KOL HA KAVOD!", window, false);
			return;
		}

		if (m_caption.getTime() <= 0) // means game over
		{
			m_caption.printMessege("NOOB! , you lost :( shame on you", window, true);
			if (m_caption.getLives() != 0)
				restartLvl();
			else
				return;
		}
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
			if (!pauseMenu(window)) // if 'exit' was pressed
				return false;
		}

		if (event.type == sf::Event::KeyReleased)
		{
			m_player.SetStandingImage(0, 1.0f);
		}
	}
	return true;
}

bool Controller::movementManger(float deltaTime)
{
	m_player.setLastLoc(); // set last location as current location
	m_player.move(m_cl.isPlayerAtBorder(), getInput(), deltaTime);
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


bool Controller::pauseMenu(sf::RenderWindow& window)
{
	sf::Clock clock;
	clock.restart();

	float deltaTime;

	while (window.isOpen())
	{
		Resources::instance().drawPauseScreen(window);
		window.display();
		if (auto event = sf::Event{}; window.waitEvent(event))
		{
			if ((event.type == sf::Event::Closed) ||
				((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
			{
				m_caption.updateTime(clock.getElapsedTime().asSeconds());
				return true;
			}

			switch (event.type)
			{

			case sf::Event::MouseButtonReleased:
				auto location = window.mapPixelToCoords(
					{ event.mouseButton.x, event.mouseButton.y });

				if (event.mouseButton.button == sf::Mouse::Button::Left)
				{
					auto buttonClicked = m_caption.handleClick(location);

					if (buttonClicked == _pauseButtons::HOME)
					{
						Resources::instance().playMusic();
						return false;
					}

					else if (buttonClicked == _pauseButtons::RESTART)
					{
						window.clear();
						restartLvl();
						return true;
					}
					else if (buttonClicked != _pauseButtons::MUSIC)
					{
						m_caption.updateTime(clock.getElapsedTime().asSeconds());
						return true;
					}
				}
			}
		}
	}
	m_caption.updateTime(clock.getElapsedTime().asSeconds());
	return true;
}

std::pair<sf::Vector2f, bool> Controller::getInput()
{
	std::pair<sf::Vector2f, bool> pair(directionInput(), shootingInput());
	return pair;
}

sf::Vector2f Controller::directionInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
	{
		//m_texture.loadFromFile("batman-right-flow.png");
		return sf::Vector2f(1, 0);
	}	
	else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
	{
		//m_texture.loadFromFile("batman-right-flow.png");
		return sf::Vector2f(-1, 0);
	}
	else
	{
		//m_texture = *Resources::instance().getTexture(_game_objects::BATMAN_STAND);
		return sf::Vector2f(0, 0);
	}
}

bool Controller::shootingInput()
{
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
	{
		return true;
	}
	return false;
}

void Controller::restartLvl()
{
	m_texture.loadFromFile("flow2.png");
	//clearLastLevel();
	m_balls.clear();
	m_board.restartBoard();
	m_world = std::make_unique<b2World>(m_garvity);
	m_player = Player(sf::Vector2f(WINDOW_WIDTH / 2, WINDOW_HEIGHT - 1.5 * WALL_SIZE + 10), m_world.get(), &m_texture, sf::Vector2u(3, 3), 0.2f, 200.0f);
	m_board.buildBackGround(m_world.get());

	//m_balls.push_back(std::move(std::make_unique<Ball>(Ball(sf::Vector2f(WINDOW_WIDTH / 3, 2 * WALL_SIZE), _ball_radius::MEGA_BIG, m_world.get(), m_rightVelocity))));
	//m_balls.push_back(std::move(std::make_unique<Ball>(Ball(sf::Vector2f(WINDOW_WIDTH / 3, 2 * WALL_SIZE), _ball_radius::BIG, m_world.get(), m_rightVelocity))));
	m_balls.push_back(std::move(std::make_unique<Ball>(Ball(sf::Vector2f(WINDOW_WIDTH / 3, 2 * WALL_SIZE), _ball_radius::MEDIUM, m_world.get(), m_rightVelocity))));
	m_balls.push_back(std::move(std::make_unique<Ball>(Ball(sf::Vector2f(WINDOW_WIDTH / 3, 2 * WALL_SIZE), _ball_radius::SMALL, m_world.get(), m_rightVelocity))));

	m_caption.resetTime();
	m_caption.updateTime(STAGE_TIME);
	m_cl.restartFlags();
	m_world->SetContactListener(&m_cl);
}