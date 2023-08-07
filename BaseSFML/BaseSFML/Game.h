#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include <iostream>
class Game
{
private:
	sf::CircleShape* shape;
public:
	std::string m_GameName;

	Game(const char* a_GameName);

	virtual bool Input(sf::RenderWindow* window);
	virtual void Update(float dt);
	virtual void Render(sf::RenderWindow* window);

	virtual void Shutdown();
};

