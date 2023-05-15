#pragma once

#include <SFML/Graphics.hpp>

class SpriteEntity
{
public:

	static const int c_defaultSpriteWidth = 32;
	static const int c_defaultSpriteHeight = 32;

	SpriteEntity(const std::string& fileName, int width = c_defaultSpriteWidth, int height = c_defaultSpriteHeight);
	virtual ~SpriteEntity();
	virtual void draw(sf::RenderWindow& window);

	void setPosition(float x, float y) { m_pos = sf::Vector2f(x, y); }
	void setPosition(const sf::Vector2f& pos) { m_pos = pos; }
	const sf::Vector2f& getPosition() const { return m_pos; }

	void setOrigin(float x, float y) { m_sprite.setOrigin(x, y); }

private:
	sf::Vector2f m_pos;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};
