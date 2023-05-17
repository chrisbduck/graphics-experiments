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

PlasmaEntity::PlasmaEntity(int width, int height) :
	SpriteEntity(width, height)
{
	setTextureData();
}

void PlasmaEntity::update()
{
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
	const float two_pi = static_cast<float>(numbers::pi) * 2.0f;
	float timeSec = timeSinceEpochInSeconds();
	unsigned index = 0;
	for (unsigned y = 0; y < height; ++y)
	{
		float yRatio = y * invHeight;
		for (unsigned x = 0; x < width; ++x)
		{
			float xRatio = x * invWidth;
			float val = (sinf(xRatio * 10.0f + cosf(yRatio * 20.0f))
				+ sinf(yRatio * 5.0f + sinf(xRatio * 30.0f))
				+ sinf((xRatio + yRatio) * 25.0f)
				+ sinf(sqrtf(xRatio * xRatio + yRatio * yRatio)))
				* 0.25f + 0.5f;
			float valR = val * 0.5f + sinf(timeSec * two_pi * 0.25f) * 0.5f;
			unsigned uVal = static_cast<unsigned>(clamp(val, 0.0f, 1.0f) * 255.0f);
			unsigned uValR = static_cast<unsigned>(clamp(valR, 0.0f, 1.0f) * 255.0f);
			auto color = 0xFF000000 | uValR << 16 | uVal << 8 | uVal;
			pixels[index] = color;
			++index;
		}
	}

	m_pTexture->update(reinterpret_cast<sf::Uint8*>(pixels.data()));
}
