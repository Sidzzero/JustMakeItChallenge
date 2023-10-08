#pragma once
#include <SFML/Graphics.hpp>
class Game
{
public:
	Game(sf::RenderWindow*win);
	void Run();
protected:
	sf::RenderWindow*m_window;
	sf::Event event;

	float dt;
	sf::Clock clock;
	std::string strFPS;

	virtual void Init();
	virtual void update();
	virtual void draw();
	virtual void handleInput(sf::Event& event);
	virtual void Cleanup();
	virtual void DebugMode();

private:
	sf::Font fntForDebug;
	sf::Text txtFPS;
	void Shutdown();


};

