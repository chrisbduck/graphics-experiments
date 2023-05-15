#pragma once

#include "SpriteEntity.h"

#include <memory>

class PlayerEntity : public SpriteEntity
{
public:
	PlayerEntity();

	static std::shared_ptr<PlayerEntity> get();
	static void setInstance(std::shared_ptr<PlayerEntity>& pInstance);
private:
	static std::shared_ptr<PlayerEntity> s_pInstance;
};
