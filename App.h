#pragma once

#include <SFML/Graphics.hpp>

#include "Background.h"
#include "ImageCache.h"
#include "Marker.h"
#include "Player.h"

class Downloader;

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
	std::shared_ptr<Background> m_pBackground;
	std::shared_ptr<Player> m_pPlayer;
	std::shared_ptr<Marker> m_pMarker;
	std::vector<std::shared_ptr<SpriteEntity>> m_entities;
};
