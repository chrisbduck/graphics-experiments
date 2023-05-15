#pragma once

#include "SpriteEntity.h"

#include <memory>

class Player : public SpriteEntity
{
public:
	Player();

	static std::shared_ptr<Player> get();
	static void setInstance(std::shared_ptr<Player>& pInstance);
private:
	static std::shared_ptr<Player> s_pInstance;
};
