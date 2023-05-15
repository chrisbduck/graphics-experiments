#include "Player.h"

#include <exception>

Player::Player() :
	SpriteEntity("data/guy2-sheet.png")
{
	setOrigin(c_defaultSpriteWidth * 0.5f, c_defaultSpriteHeight * 0.5f);
}
