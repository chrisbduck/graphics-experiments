#pragma once

#include "ImageCache.h"

#include <SFML/Graphics.hpp>
#include <chrono>

class BackgroundEntity;
class MarkerEntity;
class PlasmaEntity;
class PlayerEntity;
class SpriteEntity;

class App
{
public:
	App();
	int runMainLoop();

private:
	void initFPSDisplay();
	void processEvents();
	void update();
	void updateFPSTimer();
	void drawFPSTimer();
	void movePlayerTowardsMouse();
	void draw();

	sf::RenderWindow m_window;
	sf::Font m_font;
	sf::Text m_fpsText;
	sf::Vector2u m_lastWindowSize;
	bool m_leftMouseHeld;
	std::shared_ptr<ImageCache> m_pImageCache;
	std::shared_ptr<BackgroundEntity> m_pBackground;
	std::shared_ptr<PlayerEntity> m_pPlayer;
	std::shared_ptr<MarkerEntity> m_pBackgroundActivationMarker;
	std::shared_ptr<MarkerEntity> m_pPlasmaActivationMarker;
	std::shared_ptr<PlasmaEntity> m_pPlasma;
	std::vector<std::shared_ptr<SpriteEntity>> m_entities;
	std::chrono::high_resolution_clock::time_point m_fpsTimerStart;
	float m_fpsDisplay;
	unsigned m_fpsFrameCount;
};
