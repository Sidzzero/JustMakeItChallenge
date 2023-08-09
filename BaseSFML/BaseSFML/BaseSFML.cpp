//Starting point for an SFML Games.

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Game.h"
int main()
{
	sf::RenderWindow* window;
	window = new sf::RenderWindow(sf::VideoMode(sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SFML powered Game !");

	Game* sampleGame = new Game("SampleGame");
	
	std::cout << "Creating Window of size:" << sf::VideoMode::getDesktopMode().width << " X " << sf::VideoMode::getDesktopMode().height;
	window->setTitle(sampleGame->m_GameName);
	while (window->isOpen())
	{
		while (sampleGame->Input(window))
		{
			//process all events inside  game!
		}
		sampleGame->Update(1.0f);
		window->clear();
		sampleGame->Render(window);
		window->display();
	}

	sampleGame->Shutdown();
}
//TODO



// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
