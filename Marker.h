#pragma once

#include "SpriteEntity.h"

#include <functional>

class Player;

class Marker : public SpriteEntity
{
public:
	Marker();
	virtual void update() override;

	void setTriggerCallback(std::function<void()> callback) { m_callback = callback; }

private:
	std::function<void()> m_callback;
	bool m_isTriggering;
};
