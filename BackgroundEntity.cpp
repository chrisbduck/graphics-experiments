#include "BackgroundEntity.h"

#include <chrono>
#include <fstream>
#include <iostream>
#include <stdexcept>

using namespace std;

BackgroundEntity::BackgroundEntity(std::shared_ptr<ImageCache> pImageCache) :
	SpriteEntity("data/background.jpg"),
	m_pImageCache(pImageCache),
	m_cacheIndex(std::numeric_limits<size_t>::max())
{
	loadURLs();
}

void BackgroundEntity::update()
{
	// Check if we're waiting on a new texture and it's ready
	if (m_futureTextureAndWindowSize.has_value() && m_futureTextureAndWindowSize->wait_for(chrono::seconds::zero()) == future_status::ready)
	{
		auto value = m_futureTextureAndWindowSize->get();
		auto&& pTexture = get<0>(value);
		const auto& windowSize = get<1>(value);
		takeAndApplyTexture(move(pTexture), windowSize);
		m_futureTextureAndWindowSize.reset();
	}
}

unique_ptr<sf::Texture> BackgroundEntity::loadTexture(const std::string& fileName)
{
	auto pNewTexture = make_unique<sf::Texture>();
	if (!pNewTexture->loadFromFile(fileName))
		throw runtime_error("Failed to load file " + fileName);
	return move(pNewTexture);
}

void BackgroundEntity::takeAndApplyTexture(unique_ptr<sf::Texture>&& pTexture, const sf::Vector2u& windowSize)
{
	takeTexture(move(pTexture));
	const sf::Vector2u textureSize = m_pTexture->getSize();
	const sf::Vector2f scale(float(windowSize.x) / textureSize.x, float(windowSize.y) / textureSize.y);
	m_sprite.setScale(scale);
	m_sprite.setTextureRect(sf::IntRect(0, 0, static_cast<int>(textureSize.x), static_cast<int>(textureSize.y)));
}

void BackgroundEntity::loadImageFromFile(const std::string& fileName, const sf::Vector2u& windowSize)
{
	takeAndApplyTexture(loadTexture(fileName), windowSize);
}

void BackgroundEntity::loadImageFromFileAsync(const std::string& fileName, const sf::Vector2u& windowSize)
{
	// not trying to chain futures for now
	if (m_futureTextureAndWindowSize.has_value())
		m_futureTextureAndWindowSize->wait();

	const sf::Vector2u windowSizeCopy = windowSize;
	m_futureTextureAndWindowSize = async(launch::async,
		[this, fileName, windowSizeCopy]() { return make_tuple(loadTexture(fileName), windowSizeCopy); });
}

void BackgroundEntity::loadURLs()
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

const filesystem::path& BackgroundEntity::cacheAndGetPath(size_t index)
{
	if (index >= m_imageSourceURLs.size())
		throw runtime_error("Index out of range: " + to_string(index));
	return m_pImageCache->cacheAndGetPath(m_imageSourceURLs[index]);
}

void BackgroundEntity::loadCachedImage(size_t index, const sf::Vector2u& windowSize)
{
	const auto& path = cacheAndGetPath(index);
	loadImageFromFile(path.string(), windowSize);
}

void BackgroundEntity::loadCachedImageAsync(size_t index, const sf::Vector2u& windowSize)
{
	// not trying to chain futures for now
	if (m_futureTextureAndWindowSize.has_value())
		m_futureTextureAndWindowSize->wait();

	const sf::Vector2u windowSizeCopy = windowSize;
	m_futureTextureAndWindowSize = async(launch::async, [this, index, windowSizeCopy]()
	{
		const auto& path = cacheAndGetPath(index);
		return make_tuple(loadTexture(path.string()), windowSizeCopy);
	});
}

void BackgroundEntity::cycleCachedImageIndex()
{
	m_cacheIndex = (m_cacheIndex >= m_imageSourceURLs.size()) ? 0 : (m_cacheIndex + 1);
	cout << "cycled to background " << m_cacheIndex << endl;
}

void BackgroundEntity::cycleCachedImage(const sf::Vector2u& windowSize)
{
	cycleCachedImageIndex();
	loadCachedImage(m_cacheIndex, windowSize);
}

void BackgroundEntity::cycleCachedImageAsync(const sf::Vector2u& windowSize)
{
	cycleCachedImageIndex();
	loadCachedImageAsync(m_cacheIndex, windowSize);
}
