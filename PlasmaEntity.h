#pragma once

#include "SpriteEntity.h"

class PlasmaEntity : public SpriteEntity
{
public:
	PlasmaEntity(int width, int height);
	virtual void update() override;
private:
	void setTextureData();
	size_t toLookupIndex(float value) const;
	float fastSin(float value) const;
	float fastCos(float value) const;

	// Using lookups instead of sinf/cosf gives ~10x speedup
	std::vector<float> m_sinLookup;
	std::vector<float> m_cosLookup;
};

