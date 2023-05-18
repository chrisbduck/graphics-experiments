#include "App.h"

#include "BackgroundEntity.h"
#include "MarkerEntity.h"
#include "PlasmaEntity.h"
#include "PlayerEntity.h"
#include "Utilities.h"

#include <cstdlib>
#include <format>
#include <iostream>

using namespace std;

namespace
{
	const double c_fpsUpdateIntervalMsec = 2000.0;
}

App::App() :
	m_window(sf::VideoMode(800, 600), "Silly experimentation"),
	m_lastWindowSize(0, 0),
	m_leftMouseHeld(false),
	m_pImageCache(make_shared<ImageCache>()),
	m_pBackground(make_shared<BackgroundEntity>(m_pImageCache)),
	m_pPlayer(make_shared<PlayerEntity>()),
	m_pBackgroundActivationMarker(make_shared<MarkerEntity>()),
	m_pPlasmaActivationMarker(make_shared<MarkerEntity>()),
	m_pPlasma(make_shared<PlasmaEntity>(800, 600)),
	m_entities{ m_pBackground, m_pPlasma, m_pPlayer, m_pBackgroundActivationMarker, m_pPlasmaActivationMarker },
	m_fpsTimerStart(chrono::high_resolution_clock::now()),
	m_fpsDisplay(0.0f),
	m_fpsFrameCount(0)
{
	m_window.setFramerateLimit(30);
	m_pPlayer->setPosition(50.0f, 50.0f);
	PlayerEntity::setInstance(m_pPlayer);
	m_pBackgroundActivationMarker->setPosition(300.0f, 200.0f);
	m_pBackgroundActivationMarker->setTriggerCallback([this]()
		{
			m_pPlasma->setActive(false);
			m_pBackground->cycleCachedImageAsync(m_window.getSize());
		});
	m_pPlasmaActivationMarker->setPosition(180.0f, 320.0f);
	m_pPlasmaActivationMarker->setTriggerCallback([this]() { m_pPlasma->setActive(!m_pPlasma->isActive()); });

	srand(static_cast<unsigned>(time(nullptr)));

	initFPSDisplay();
}

void App::processEvents()
{
	sf::Event event;
	while (m_window.pollEvent(event))
	{
		switch (event.type)
		{
		case sf::Event::Closed:
			m_window.close();
			break;
		case sf::Event::Resized:
			cout << "window resized to " << event.size.width << " x " << event.size.height << endl;
			break;
		case sf::Event::MouseButtonPressed:
		case sf::Event::MouseButtonReleased:
			if (event.mouseButton.button == sf::Mouse::Left)
				m_leftMouseHeld = event.type == sf::Event::MouseButtonPressed;
			break;
		case sf::Event::MouseLeft:
			// mouse went outside the window; make sure we don't get confused
			m_leftMouseHeld = false;
			break;
		}
	}
}

void App::update()
{
	if (m_leftMouseHeld)
		movePlayerTowardsMouse();

	ranges::for_each(m_entities, &SpriteEntity::update);

	updateFPSTimer();
}

void App::initFPSDisplay()
{
	if (!m_font.loadFromFile("c:\\windows\\fonts\\Georgia.ttf"))
		throw runtime_error("Failed to load font");
	m_fpsText.setFont(m_font);
	m_fpsText.setCharacterSize(32);
	m_fpsText.setFillColor(sf::Color::Yellow);
}

void App::updateFPSTimer()
{
	++m_fpsFrameCount;

	// Check if it's been long enough to update the FPS counter
	auto now = chrono::high_resolution_clock::now();
	auto elapsedMS = float(chrono::duration_cast<chrono::milliseconds>(now - m_fpsTimerStart).count());
	if (elapsedMS < c_fpsUpdateIntervalMsec)
		return;

	// Update the counter
	m_fpsDisplay = m_fpsFrameCount * 1000.0f / elapsedMS;

	// Set up the next timer
	m_fpsFrameCount = 0;
	m_fpsTimerStart = now;
}

void App::drawFPSTimer()
{
	m_fpsText.setString(format("FPS: {:.1f}", m_fpsDisplay));
	m_fpsText.setPosition(16.0f, m_window.getSize().y - 48.0f);
	m_window.draw(m_fpsText);
}

void App::movePlayerTowardsMouse()
{
	static const float c_maxSpeed = 5.0f;
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
	sf::Vector2f playerPosition = m_pPlayer->getPosition();
	sf::Vector2f offset = sf::Vector2f(mousePosition) - playerPosition;
	float offsetMagnitude = magnitude(offset);
	float speedScale = (offsetMagnitude < 0.1f) ? 0.0f : min(c_maxSpeed / offsetMagnitude, 1.0f);
	sf::Vector2f velocity = offset * speedScale;
	m_pPlayer->setPosition(playerPosition + velocity);
}

void App::draw()
{
	m_window.clear();
	ranges::for_each(m_entities, [this](shared_ptr<SpriteEntity>& entity) { entity->draw(m_window); });
	drawFPSTimer();
	m_window.display();
}

int App::runMainLoop()
{
	while (true)
	{
		processEvents();
		if (!m_window.isOpen())
			return 0;

		update();
		draw();
	}
}
