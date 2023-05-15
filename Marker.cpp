#include "Marker.h"

#include "Player.h"
#include "Utilities.h"

Marker::Marker() :
	SpriteEntity("data/diamond.png"),
	m_isTriggering(false)
{
	setOrigin(c_defaultSpriteWidth * 0.5f, c_defaultSpriteHeight * 0.5f);
}

void Marker::update()
{
	const auto player = Player::get();
	const sf::Vector2f offset = player->getPosition() - getPosition();
	bool shouldTrigger = magnitude(offset) < SpriteEntity::c_defaultSpriteWidth;
	if (shouldTrigger != m_isTriggering)
	{
		m_isTriggering = shouldTrigger;
		if (shouldTrigger)
			m_callback();
	}
}
