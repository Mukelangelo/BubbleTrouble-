#include "Player.h"

Player::Player(sf::Vector2f pos) {
	m_sprite = sf::Sprite(*Resources::instance().getTexture(0));
	m_sprite.setPosition(pos);
	m_lastLoc = m_location = pos;
	m_speedPerSecond = m_sprite.getScale().x * 200;
	m_powers.push_back(std::make_unique<Weapon>(Weapon()));
}

void Player::draw(sf::RenderWindow& window) {
	for (auto& pow : m_powers) {
		pow->draw(window);
	}
	window.draw(m_sprite);
}

void Player::move(sf::Time deltaTime) {
	m_sprite.move(m_direction * m_speedPerSecond * deltaTime.asSeconds());
	m_location = m_sprite.getPosition();
}

void Player::shoot() {
	m_powers[0]->activate(m_sprite.getPosition() + sf::Vector2f(50, WALL_SIZE)); // need to center more efficintly
	
}

void Player::handlePowers() {
	for (auto& pow : m_powers) {
		pow->checkEnd();
	}
}