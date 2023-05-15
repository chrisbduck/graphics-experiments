#pragma once

#include "ImageCache.h"
#include "SpriteEntity.h"

#include <SFML/Graphics.hpp>

class Background : public SpriteEntity
{
public:
	explicit Background(std::shared_ptr<ImageCache> imageCache);

	void loadImageFromFile(const std::string& fileName, const sf::Window& window);
	void loadCachedImage(size_t index, const sf::Window& window);
	void cycleCachedImage(const sf::Window& window);

private:

	void loadURLs();

	std::shared_ptr<ImageCache> m_pImageCache;
	std::vector<std::string> m_imageSourceURLs;
	size_t m_cacheIndex;
};

