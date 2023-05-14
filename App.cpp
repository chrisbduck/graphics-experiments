#include "App.h"

#include <SFML/Network.hpp>
#include <format>
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
	m_background.draw(m_window);
	m_player.draw(m_window);
	m_window.display();
}

static const char* const imgURL = "https://live.staticflickr.com/65535/52884078630_008fd806e0_h.jpg";
static const char* const imgURL2 = "https://live.staticflickr.com/65535/52562967125_ac3d7ea160_k.jpg";
static const char* const imgURL3 = "https://live.staticflickr.com/65535/50080607633_77ab082d23_h.jpg";
static const char* const imgURL4 = "https://live.staticflickr.com/65535/52875829685_ddf074cfff_h.jpg";
// https://live.staticflickr.com/65535/52856866967_6a5053e26d_h.jpg
// https://live.staticflickr.com/65535/50581737261_28071fbc28_h.jpg
// https://live.staticflickr.com/65535/52800537723_0cbfc2fb3d_h.jpg
// https://live.staticflickr.com/65535/52753570963_b638e12edf_h.jpg
// https://live.staticflickr.com/5790/20945867598_c8487302ca_h.jpg
// https://live.staticflickr.com/4003/4656802696_a8d1c06997_c.jpg
// https://live.staticflickr.com/4016/4629801399_7d2843bc64_c.jpg

int App::runMainLoop()
{
	//m_downloader.download(imgURL, "test.jpg");
	m_background.loadImageFromFile("test.jpg", m_window);

	while (true)
	{
		processEvents();
		if (!m_window.isOpen())
			return 0;

		update();
		draw();
	}
}
