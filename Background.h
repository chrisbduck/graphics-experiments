#pragma once

#include "ImageCache.h"
#include "SpriteEntity.h"

#include <SFML/Graphics.hpp>
#include <future>

class Background : public SpriteEntity
{
public:
	explicit Background(std::shared_ptr<ImageCache> imageCache);

	virtual void update() override;

	void loadImageFromFile(const std::string& fileName, const sf::Vector2u& windowSize);
	void loadImageFromFileAsync(const std::string& fileName, const sf::Vector2u& windowSize);
	void loadCachedImage(size_t index, const sf::Vector2u& windowSize);
	void loadCachedImageAsync(size_t index, const sf::Vector2u& windowSize);
	void cycleCachedImage(const sf::Vector2u& windowSize);
	void cycleCachedImageAsync(const sf::Vector2u& windowSize);

	std::unique_ptr<sf::Texture> loadTexture(const std::string& fileName);
	void takeAndApplyTexture(std::unique_ptr<sf::Texture>&& pTexture, const sf::Vector2u& windowSize);

private:

	void loadURLs();
	void cycleCachedImageIndex();
	const std::filesystem::path& cacheAndGetPath(size_t index);

	std::shared_ptr<ImageCache> m_pImageCache;
	std::vector<std::string> m_imageSourceURLs;
	size_t m_cacheIndex;
	std::optional<std::future<std::tuple<std::unique_ptr<sf::Texture>, sf::Vector2u>>> m_futureTextureAndWindowSize;
};

