#pragma once
#include <SFML/Graphics.hpp>
class Game
{
public:
	Game(sf::Window *win);

private :
	sf::Window *m_window;
	void update();
	void draw();
	void handleInput();
};

