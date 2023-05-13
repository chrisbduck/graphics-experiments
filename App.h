#pragma once

#include <SFML/Graphics.hpp>

#include "Player.h"

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
	Player m_player;
	bool m_leftMouseHeld;
};
