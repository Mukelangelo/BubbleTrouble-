#include "Player.h"

Player::Player(sf::Vector2f pos) {
	//this is temp:
	m_sprite = sf::RectangleShape(sf::Vector2f(100, 100));
	m_sprite.setFillColor(sf::Color::Black);
	m_sprite.setPosition(sf::Vector2f(500, 500));
	//
	m_speedPerSecond = m_sprite.getScale().x * 200;
}

void Player::draw(sf::RenderWindow& window) {
	window.draw(m_sprite);
}

void Player::move(sf::Time deltaTime) {
	m_sprite.move(m_direction * m_speedPerSecond * deltaTime.asSeconds());
	m_location = m_sprite.getPosition();
}

void Player::shoot() {

}