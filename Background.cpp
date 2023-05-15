#include "Background.h"

#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace std;

Background::Background(ImageCache& imageCache) :
	m_isLoaded(false),
	m_imageCache(imageCache),
	m_cacheIndex(0)
{
	loadURLs();
}

void Background::draw(sf::RenderWindow& window)
{
	if (m_isLoaded)
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
	m_isLoaded = true;
}

void Background::loadURLs()
{
	ifstream urlFileStream("urls.txt");
	if (!urlFileStream.good())
		throw runtime_error("Couldn't open URLs file");

	hash<string> hasher;
	while (urlFileStream.good())
	{
		string line;
		urlFileStream >> line;
		if (line.length() > 0 && !line.starts_with('#'))
			m_imageSourceURLs.push_back(line);
	}
}

void Background::loadCachedImage(size_t index, const sf::Window& window)
{
	if (index >= m_imageSourceURLs.size())
		throw runtime_error("Index out of range: " + to_string(index));
	
	const auto& path = m_imageCache.cacheAndGetPath(m_imageSourceURLs[index]);
	loadImageFromFile(path.string(), window);
}

void Background::cycleCachedImage(const sf::Window& window)
{
	m_cacheIndex = (m_cacheIndex == 1) ? 0 : 1;
	cout << "cycled to background " << m_cacheIndex << endl;
	loadCachedImage(m_cacheIndex, window);
}
