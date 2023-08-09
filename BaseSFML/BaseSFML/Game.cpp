#include "Game.h"

Game::Game(const char* a_GameName) :m_GameName(a_GameName)
{
	std::cout << "Challenge Games Made using SFML\n";

	shape = new sf::CircleShape(100.0f);
	shape->setFillColor(sf::Color::Green);
	std::cout << "Initiailizing Game:" + m_GameName;
}

bool Game::Input(sf::RenderWindow* window)
{
	sf::Event event;
	while (window->pollEvent(event))
	{
		if (event.type == sf::Event::Closed)
		{
			window->close();
		}
		if (event.type == sf::Event::KeyPressed)
		{
			if (event.key.code == sf::Keyboard::Escape)
			{
			  window->close();
			}
		}
		//keep window here only !
	}
	return false;
}

void Game::Update(float dt)
{

}

void Game::Render(sf::RenderWindow* window)
{
	window->draw(*shape);
}

void Game::Shutdown()
{

}
