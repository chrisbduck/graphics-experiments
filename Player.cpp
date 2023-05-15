#include "Player.h"

#include <stdexcept>

using namespace std;

shared_ptr<Player> Player::s_pInstance;

Player::Player() :
	SpriteEntity("data/guy2-sheet.png")
{
	setTextureSize(c_defaultSpriteWidth, c_defaultSpriteHeight);
	setOrigin(c_defaultSpriteWidth * 0.5f, c_defaultSpriteHeight * 0.5f);
}

shared_ptr<Player> Player::get()
{
	if (s_pInstance == nullptr)
		throw runtime_error("No player found");
	return s_pInstance;
}

void Player::setInstance(shared_ptr<Player>& pInstance)
{
	s_pInstance = pInstance;
}
