#include "Player.h"

#include <exception>

namespace
{
	const int s_spriteWidth = 32;
	const int s_spriteHeight = 32;
}

Player::Player() :
	m_pos(0.0f, 0.0f)
{
	if (!m_texture.loadFromFile("data/guy2-sheet.png"))
		throw std::runtime_error("Failed to load player texture");
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, s_spriteWidth, s_spriteHeight));
	m_sprite.setOrigin(s_spriteWidth * 0.5f, s_spriteHeight * 0.5f);
}

void Player::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_pos);
	window.draw(m_sprite);
}
