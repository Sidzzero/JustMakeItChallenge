#include "Game.h"
#include <iostream>

Game::Game(sf::RenderWindow* win) : m_window{ win }, event{}, clock{}, strFPS{"FPS:"}
{
	Init();
}
void Game::Init()
{
	fntForDebug.loadFromFile("Font/arial.ttf");
	txtFPS.setFont(fntForDebug);
	txtFPS.setString("FPS:over 9000");
	txtFPS.setFillColor(sf::Color::White);
}
void Game::Run()
{
	//m_window->setFramerateLimit(30);
	//Main Loop
	while (m_window->isOpen())
	{
		dt = clock.restart().asSeconds();

		//Event LOOP Enter
		while (m_window->pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
			{
				m_window->close();
				Shutdown();
			}
			handleInput(event);
		}
		//Event LOOP Exit
		update();//CHECK IF NEEDS TO BE DOWN
		m_window->clear();
		//Draw calls
		draw();
		DebugMode();
		m_window->display();
		
		
	}
}

void Game::Shutdown()
{
	Cleanup();
}

void Game::update()
{

}

void Game::draw()
{

}

void Game::handleInput(sf::Event& event)
{

}

void Game::Cleanup()
{
	std::cout << "Cleanup";
}

void Game::DebugMode()
{
	txtFPS.setString("FPS:" + std::to_string(1.0f / dt));
	m_window->draw(txtFPS);
}



