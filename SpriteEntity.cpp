#include "SpriteEntity.h"

SpriteEntity::SpriteEntity(const std::string& fileName, int width, int height) :
	m_pos(0.0f, 0.0f)
{
	if (!m_texture.loadFromFile(fileName))
		throw std::runtime_error("Failed to load texture: " + fileName);
	m_sprite.setTexture(m_texture);
	m_sprite.setTextureRect(sf::IntRect(0, 0, width, height));
}

SpriteEntity::~SpriteEntity()
{
}

void SpriteEntity::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_pos);
	window.draw(m_sprite);
}
