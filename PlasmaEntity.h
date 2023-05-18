#pragma once

#include "SpriteEntity.h"

class PlasmaEntity : public SpriteEntity
{
public:
	PlasmaEntity(int width, int height);
	virtual void update() override;
	virtual void draw(sf::RenderWindow& window) override;

	void setActive(bool active) { m_isActive = active; }
	bool isActive() const { return m_isActive; }

private:
	void setTextureData();
	size_t toLookupIndex(float value) const;
	float fastSin(float value) const;
	float fastCos(float value) const;

	bool m_isActive;

	// Using lookups instead of sinf/cosf gives ~10x speedup
	std::vector<float> m_sinLookup;
	std::vector<float> m_cosLookup;
};

