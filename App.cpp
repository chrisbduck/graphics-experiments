#include "App.h"

#include "Utilities.h"

#include <SFML/Network.hpp>
#include <format>
#include <iostream>

using namespace std;

App::App() :
	m_window(sf::VideoMode(800, 600), "SFML works!"),
	m_lastWindowSize(0, 0),
	m_leftMouseHeld(false),
	m_pImageCache(make_shared<ImageCache>()),
	m_pBackground(make_shared<Background>(m_pImageCache)),
	m_pPlayer(make_shared<Player>()),
	m_pMarker(make_shared<Marker>()),
	m_entities{ m_pBackground, m_pPlayer, m_pMarker }
{
	m_window.setFramerateLimit(30);
	m_pPlayer->setPosition(50.0f, 50.0f);
	Player::setInstance(m_pPlayer);
	m_pMarker->setPosition(300.0f, 200.0f);
	m_pMarker->setTriggerCallback([this]() { m_pBackground->cycleCachedImage(m_window); });
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
