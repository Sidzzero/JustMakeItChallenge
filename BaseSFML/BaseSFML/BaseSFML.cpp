//Starting point for an SFML Games.

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Game.h"
int main()
{
    std::cout << "Challenge Games Made using SFML\n";
    std::cout <<"Creating Window of size:" << sf::VideoMode::getDesktopMode().width << " X " << sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode (sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SFML powered Game ");
    sf::CircleShape shape(100.0f);
    shape.setFillColor(sf::Color::Green);

    //Game Decleartions
    Game* m_game = nullptr;
    m_game = new Game();
    m_game->Init(true);
    
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
        }
        window.clear();
        m_game->Update(window);
        window.display();
    }

    m_game->Cleanup();
    delete m_game;
    m_game = nullptr;
}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
