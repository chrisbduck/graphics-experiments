#pragma once

#include <SFML/Graphics.hpp>

class Player
{
public:
	Player();
	void setPosition(float x, float y) { m_pos = sf::Vector2f(x, y); }
	void setPosition(const sf::Vector2f& pos) { m_pos = pos; }
	const sf::Vector2f& getPosition() const { return m_pos; }
	void draw(sf::RenderWindow& window);
private:
	sf::Vector2f m_pos;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};
