#include "App.h"

#include <iostream>

using namespace std;

App::App() :
	m_window(sf::VideoMode(800, 600), "SFML works!"),
	m_lastWindowSize(0, 0),
	m_leftMouseHeld(false)
{
	m_window.setFramerateLimit(30);
	m_player.setPosition(50.0f, 50.0f);
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
}

void App::movePlayerTowardsMouse()
{
	static const float c_maxSpeed = 5.0f;
	sf::Vector2i mousePosition = sf::Mouse::getPosition(m_window);
	sf::Vector2f playerPosition = m_player.getPosition();
	sf::Vector2f offset = sf::Vector2f(mousePosition) - playerPosition;
	float offsetMagnitude = sqrt(offset.x * offset.x + offset.y * offset.y);
	float speedScale = (offsetMagnitude < 0.1f) ? 0.0f : min(c_maxSpeed / offsetMagnitude, 1.0f);
	sf::Vector2f velocity = offset * speedScale;
	m_player.setPosition(playerPosition + velocity);
}

void App::draw()
{
	m_window.clear();
	const auto windowSize = m_window.getSize();
	const auto radius = static_cast<float>(min(windowSize.x, windowSize.y));
	sf::CircleShape shape(radius, 60U);
	shape.setFillColor(sf::Color::Green);
	m_window.draw(shape);
	m_player.draw(m_window);
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
