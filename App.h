#pragma once

#include <SFML/Graphics.hpp>

#include "Background.h"
#include "ImageCache.h"
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
	ImageCache m_imageCache;
	Background m_background;
	Player m_player;
	bool m_leftMouseHeld;
};
