#include "Background.h"

#include <stdexcept>

using namespace std;

Background::Background()
{
}

void Background::draw(sf::RenderWindow& window)
{
	window.draw(m_sprite);
}

void Background::loadImageFromFile(const std::string& fileName, const sf::Window& window)
{
	if (!m_texture.loadFromFile(fileName))
		throw runtime_error("Failed to load file " + fileName);
	m_sprite.setTexture(m_texture);
	const sf::Vector2u windowSize = window.getSize();
	const sf::Vector2u textureSize = m_texture.getSize();
	m_sprite.setScale(float(windowSize.x) / textureSize.x, float(windowSize.y) / textureSize.y);
	m_sprite.setPosition(0.0f, 0.0f);
}
