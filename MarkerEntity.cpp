#include "MarkerEntity.h"

#include "PlayerEntity.h"
#include "Utilities.h"

MarkerEntity::MarkerEntity() :
	SpriteEntity("data/diamond.png"),
	m_isTriggering(false)
{
	setOrigin(c_defaultSpriteWidth * 0.5f, c_defaultSpriteHeight * 0.5f);
}

void MarkerEntity::update()
{
	const auto player = PlayerEntity::get();
	const sf::Vector2f offset = player->getPosition() - getPosition();
	bool shouldTrigger = magnitude(offset) < SpriteEntity::c_defaultSpriteWidth;
	if (shouldTrigger != m_isTriggering)
	{
		m_isTriggering = shouldTrigger;
		if (shouldTrigger)
			m_callback();
	}
}
