#pragma once

#include <SFML/Graphics.hpp>

class Background
{
public:
	Background();
	void draw(sf::RenderWindow& window);
	void loadImageFromFile(const std::string& fileName, const sf::Window& window);

private:
	sf::Texture m_texture;
	sf::Sprite m_sprite;
};

