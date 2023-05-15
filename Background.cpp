#include "Background.h"

#include <fstream>
#include <stdexcept>
#include <iostream>

using namespace std;

Background::Background(std::shared_ptr<ImageCache> pImageCache) :
	SpriteEntity("data/background.jpg"),
	m_pImageCache(pImageCache),
	m_cacheIndex(std::numeric_limits<size_t>::max())
{
	loadURLs();
}

void Background::loadImageFromFile(const std::string& fileName, const sf::Window& window)
{
	{
		auto pNewTexture = make_unique<sf::Texture>();
		if (!pNewTexture->loadFromFile(fileName))
			throw runtime_error("Failed to load file " + fileName);
		takeTexture(move(pNewTexture));
	}
	const sf::Vector2u windowSize = window.getSize();
	const sf::Vector2u textureSize = m_pTexture->getSize();
	const sf::Vector2f scale(float(windowSize.x) / textureSize.x, float(windowSize.y) / textureSize.y);
	m_sprite.setScale(scale);
	m_sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(textureSize.x), static_cast<int>(textureSize.y)));
}

void Background::loadURLs()
{
	ifstream urlFileStream("urls.txt");
	if (!urlFileStream.good())
		throw runtime_error("Couldn't open URLs file");

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
	
	const auto& path = m_pImageCache->cacheAndGetPath(m_imageSourceURLs[index]);
	loadImageFromFile(path.string(), window);
}

void Background::cycleCachedImage(const sf::Window& window)
{
	m_cacheIndex = (m_cacheIndex == 0) ? 1 : 0;
	cout << "cycled to background " << m_cacheIndex << endl;
	loadCachedImage(m_cacheIndex, window);
}
