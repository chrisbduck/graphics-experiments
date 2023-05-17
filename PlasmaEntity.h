#pragma once

#include "SpriteEntity.h"

class PlasmaEntity : public SpriteEntity
{
public:
	PlasmaEntity(int width, int height);
	virtual void update() override;
private:
	void setTextureData();
};

