#pragma once

#include <SFML\Graphics.hpp>

class Animation
{
public:
	Animation() = default;
	Animation(sf::Texture* texture, sf::Vector2u imageCount, float swithTime);
	~Animation() = default;

	void Update(int row, float deltaTime, bool faceRight);
	void setTexture();

	sf::IntRect uvRect;

private:
	sf::Vector2u m_imageCount;
	sf::Vector2u m_currentImage;
	float m_totalTime;
	float m_switchTime;
};