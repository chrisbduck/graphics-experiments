#pragma once

#include "ImageCache.h"

#include <SFML/Graphics.hpp>

class Background
{
public:
	explicit Background(ImageCache& imageCache);
	void draw(sf::RenderWindow& window);
	void loadImageFromFile(const std::string& fileName, const sf::Window& window);
	void loadCachedImage(size_t index, const sf::Window& window);

private:

	void loadURLs();

	bool m_isLoaded;
	sf::Texture m_texture;
	sf::Sprite m_sprite;
	ImageCache& m_imageCache;
	std::vector<std::string> m_imageSourceURLs;
};

