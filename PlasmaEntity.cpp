#include "PlasmaEntity.h"

#include "Utilities.h"

#include <chrono>
#include <cmath>
#include <cstdlib>
#include <iostream>
#include <numbers>
#include <stdexcept>
#include <ranges>

using namespace std;

namespace
{
	constexpr size_t c_lookupSize = 1 << 10;
	constexpr size_t c_lookupSizeMask = c_lookupSize - 1;
	constexpr float twoPi = static_cast<float>(numbers::pi) * 2.0f;
	constexpr float c_sinCosToLookupScale = static_cast<float>(c_lookupSize) / twoPi;
}

PlasmaEntity::PlasmaEntity(int width, int height) :
	SpriteEntity(width, height),
	m_sinLookup(c_lookupSize),
	m_cosLookup(c_lookupSize),
	m_isActive(false)
{
	setTextureData();
	constexpr float scale = twoPi / c_lookupSize;
	for (size_t index = 0; index < c_lookupSize; ++index)
	{
		float value = static_cast<float>(index) * scale;
		m_sinLookup[index] = sinf(value);
		m_cosLookup[index] = cosf(value);
	}
}

size_t PlasmaEntity::toLookupIndex(float value) const
{
	return static_cast<size_t>(value * c_sinCosToLookupScale) & c_lookupSizeMask;
}

float PlasmaEntity::fastSin(float value) const
{
	return m_sinLookup[toLookupIndex(value)];
}

float PlasmaEntity::fastCos(float value) const
{
	return m_cosLookup[toLookupIndex(value)];
}

void PlasmaEntity::update()
{
	if (m_isActive)
		setTextureData();
}

void PlasmaEntity::setTextureData()
{
	const auto& size = m_pTexture->getSize();
	const auto width = size.x;
	const auto height = size.y;
	vector<sf::Uint32> pixels(width * height);

	// Generate a plasma
	float invWidth = 1.0f / width;
	float invHeight = 1.0f / height;
	const float timeSec = timeSinceEpochInSeconds();
	const float timeTimesTwoPi = timeSec * twoPi;
	const float timeR = timeSec * (1.0f / 3.0f);
	const float timeG = timeSec * (1.0f / 5.0f);
	const float timeB = timeSec * (1.0f / 7.0f);
	unsigned index = 0;
	for (unsigned y = 0; y < height; ++y)
	{
		float yRatio = y * invHeight;
		for (unsigned x = 0; x < width; ++x)
		{
			float xRatio = x * invWidth;
			float valBase = fastSin(yRatio * 5.0f + fastSin(xRatio * 30.0f))
				+ fastSin((xRatio + yRatio) * 25.0f)
				+ fastSin(xRatio * xRatio + yRatio * yRatio);	// originally sqrtf, but it's slow and doesn't affect things much
			float yCosVal = fastCos(yRatio * 20.0f);
			float valR = (fastSin((xRatio + timeR) * 10.0f + yCosVal) + valBase) * 0.25f + 0.4f;
			float valG = (fastSin((xRatio + timeG) * 10.0f + yCosVal) + valBase) * 0.25f + 0.4f;
			float valB = (fastSin((xRatio + timeB) * 10.0f + yCosVal) + valBase) * 0.25f + 0.4f;
			unsigned uValR = static_cast<unsigned>(clamp(valR, 0.0f, 1.0f) * 255.0f);
			unsigned uValG = static_cast<unsigned>(clamp(valG, 0.0f, 1.0f) * 255.0f);
			unsigned uValB = static_cast<unsigned>(clamp(valB, 0.0f, 1.0f) * 255.0f);
			auto color = 0xFF000000U | uValB << 16 | uValG << 8 | uValR;
			pixels[index] = color;
			++index;
		}
	}

	m_pTexture->update(reinterpret_cast<sf::Uint8*>(pixels.data()));
}

void PlasmaEntity::draw(sf::RenderWindow& window)
{
	if (m_isActive)
		SpriteEntity::draw(window);
}
