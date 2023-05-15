#include "PlayerEntity.h"

#include <stdexcept>

using namespace std;

shared_ptr<PlayerEntity> PlayerEntity::s_pInstance;

PlayerEntity::PlayerEntity() :
	SpriteEntity("data/guy2-sheet.png")
{
	setTextureSize(c_defaultSpriteWidth, c_defaultSpriteHeight);
	setOrigin(c_defaultSpriteWidth * 0.5f, c_defaultSpriteHeight * 0.5f);
}

shared_ptr<PlayerEntity> PlayerEntity::get()
{
	if (s_pInstance == nullptr)
		throw runtime_error("No player found");
	return s_pInstance;
}

void PlayerEntity::setInstance(shared_ptr<PlayerEntity>& pInstance)
{
	s_pInstance = pInstance;
}
