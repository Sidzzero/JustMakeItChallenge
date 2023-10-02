#pragma once
#include "Game.h"
class SnakeGame :public Game
{
public:
	SnakeGame(sf::RenderWindow* win);
protected:
	void update() override;
	void draw() override;
	void handleInput(sf::Event& event) override ;
	void Cleanup() override;
};

