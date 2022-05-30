#pragma once

#include "macros.h"

class Power {
public:
	Power();

	int getPower();
	bool timeBased();
	bool getActiveStatus();
	virtual void activate(const sf::Vector2f& pos) = 0;
	virtual void draw(sf::RenderWindow & window) = 0;
	virtual void checkEnd() = 0;
	virtual void forceEnd() {}
	void setActive();

	virtual ~Power() = default;

protected:
	bool m_isTimeBased;
	int m_value;
	bool m_isActive;
	sf::RectangleShape m_obj;
};