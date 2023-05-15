#pragma once

#include <SFML/Graphics.hpp>

#include "ImageCache.h"

class BackgroundEntity;
class MarkerEntity;
class PlayerEntity;
class SpriteEntity;

class App
{
public:
	App();
	int runMainLoop();

private:
	void processEvents();
	void update();
	void movePlayerTowardsMouse();
	void draw();

	sf::RenderWindow m_window;
	sf::Vector2u m_lastWindowSize;
	bool m_leftMouseHeld;
	std::shared_ptr<ImageCache> m_pImageCache;
	std::shared_ptr<BackgroundEntity> m_pBackground;
	std::shared_ptr<PlayerEntity> m_pPlayer;
	std::shared_ptr<MarkerEntity> m_pMarker;
	std::vector<std::shared_ptr<SpriteEntity>> m_entities;
};
