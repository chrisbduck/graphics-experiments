#pragma once

#include <SFML/Graphics.hpp>

class SpriteEntity
{
public:

	static const int c_defaultSpriteWidth = 32;
	static const int c_defaultSpriteHeight = 32;

	SpriteEntity(const std::string& fileName);	// construct with texture from file
	SpriteEntity(int width, int height);		// construct with empty texture
	virtual ~SpriteEntity();
	virtual void update();
	virtual void draw(sf::RenderWindow& window);

	void setPosition(float x, float y) { m_pos = sf::Vector2f(x, y); }
	void setPosition(const sf::Vector2f& pos) { m_pos = pos; }
	const sf::Vector2f& getPosition() const { return m_pos; }

	void setOrigin(float x, float y) { m_sprite.setOrigin(x, y); }
	void setTextureSize(int width, int height);

	void takeTexture(std::unique_ptr<sf::Texture>&& pTexture);

protected:
	// normally we'd make these private and add accessors, but I'm skipping for this experiment
	sf::Vector2f m_pos;
	std::unique_ptr<sf::Texture> m_pTexture;
	sf::Sprite m_sprite;

private:
	SpriteEntity();		// internal partial constructor
};
