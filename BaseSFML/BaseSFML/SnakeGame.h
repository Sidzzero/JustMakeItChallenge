#pragma once
#include "Game.h"
#include <deque>
enum  eDirection
{
	Up,
	Down,
	Left,
	Right
};
enum eGameState
{
	Playing,
	Paused,
	Menu,
	GameOver
};

class SnakeGame :public Game
{
public:
	SnakeGame(sf::RenderWindow* win);
private:
	bool CheckCollision();
protected:
	eGameState state;
	//UI
	sf::Font fntUI;
	sf::Text txtCurrentState;
	
	//Snake Related
	eDirection dir = eDirection::Right;
	std::deque<sf::CircleShape*> snakeBody;
	sf::Vector2f direction = sf::Vector2f(1.0f, 0.0f);
	//Snake Number
	std::vector<sf::Text*> snakeNumber;
	sf::Vector2f vTextOffset;

	float fWaitTime = 0.0f;
	float snakeUpdateTime = 0.25f;
	sf::RectangleShape food;
	
	void Init() override;
	void update() override;
	void draw() override;
	void handleInput(sf::Event& event) override ;
	void Cleanup() override;
};

