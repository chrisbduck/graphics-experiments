#include "SpriteEntity.h"

using namespace std;

SpriteEntity::SpriteEntity(const std::string& fileName) :
	m_pos(0.0f, 0.0f),
	m_pTexture(make_unique<sf::Texture>())
{
	if (!m_pTexture->loadFromFile(fileName))
		throw std::runtime_error("Failed to load texture: " + fileName);
	m_sprite.setTexture(*m_pTexture);
}

SpriteEntity::~SpriteEntity()
{
}

void SpriteEntity::setTextureSize(int width, int height)
{
	m_sprite.setTextureRect(sf::IntRect(0, 0, width, height));
}

void SpriteEntity::update()
{
}

void SpriteEntity::draw(sf::RenderWindow& window)
{
	m_sprite.setPosition(m_pos);
	window.draw(m_sprite);
}

void SpriteEntity::takeTexture(unique_ptr<sf::Texture>&& pTexture)
{
	m_pTexture.reset(pTexture.release());
	m_sprite.setTexture(*m_pTexture);
}
