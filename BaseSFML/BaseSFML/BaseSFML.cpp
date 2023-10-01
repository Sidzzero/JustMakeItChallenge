//Starting point for an SFML Games.

#include <iostream>
#include "SFML/Graphics.hpp"
#include "Game.h"
#include <string>
#include <vector>
#include <queue>
#include <algorithm>
enum  eDirection
{
    Up,
    Down,
    Left,
    Right
};
int main()
{
    std::cout << "Challenge Games Made using SFML\n";
    std::cout <<"Creating Window of size:" << sf::VideoMode::getDesktopMode().width << " X " << sf::VideoMode::getDesktopMode().height;
    sf::RenderWindow window(sf::VideoMode (sf::VideoMode::getDesktopMode().width, sf::VideoMode::getDesktopMode().height), "SFML powered Game ");

    //Body parts

    sf::CircleShape shape(30.0f);
    shape.setFillColor(sf::Color::Green);
    std::deque<sf::CircleShape*> snakeBody;
    sf::Vector2f direction = sf::Vector2f(1.0f, 0.0f);
    eDirection dir = eDirection::Right;
    for (int i=0;i<5;i++)
    {
        auto temp = new sf::CircleShape(30.0f);
        temp->setPosition(sf::Vector2f(400 - i*(63), 400));
        temp->setOutlineColor(sf::Color::Yellow);
        temp->setOutlineThickness(3.0f);
        temp->setFillColor(sf::Color::Green);
        snakeBody.push_back(temp) ;
    }

    //FPS calculations...
    sf::Font fpsFont;
    sf::Text fpsText;
    fpsFont.loadFromFile("Font/arial.ttf");
    std::cout<<"FontInfo:"+fpsFont.getInfo().family;
    fpsText.setFont(fpsFont);
    fpsText.setString("FPS:over 9000");
    fpsText.setFillColor(sf::Color::White);
    
    float dt;
    sf::Clock clock;
    std::string strFPS;

    float dy = 0;
    float fWaitTime = 0.0f;
    float snakeUpdateTime = 0.25f;
    while (window.isOpen())
    {
        
        sf::Event event;
        window.setFramerateLimit(30);
        dt = clock.restart().asSeconds();
        float fps = 1.0f / dt;
        strFPS = std::to_string(fps);
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
            {
                window.close();
            }
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Right)
                {
                    if (dir != eDirection::Left )
                    {
                        direction.x = 1.0f;
                        direction.y = 0.0f;
                        dir = eDirection::Right;
                    }
                  
                }
                else if (event.key.code == sf::Keyboard::Left)
                {
                    if (dir != eDirection::Right)
                    {
                        direction.x = -1.0f;
                        direction.y = 0.0f;
                        dir = eDirection::Left;
                    }

                }
                else if (event.key.code == sf::Keyboard::Up)
                {
                    if (dir != eDirection::Down)
                    {
                        direction.x = 0.0f;
                        direction.y = -1.0f;
                        dir = eDirection::Up;
                    }

                }
                else if (event.key.code == sf::Keyboard::Down)
                {
                    if (dir != eDirection::Up)
                    {
                        direction.x = 0.0f;
                        direction.y = 1.0f;
                        dir = eDirection::Down;
                    }

                }
            }

        }
        window.clear();
      //  window.draw(shape);

        if (fWaitTime> snakeUpdateTime)
        {
            fWaitTime = 0;
            auto temp_Back = snakeBody.back();
            snakeBody.pop_back();
            auto temp_NewPos = snakeBody.front()->getPosition() + 63.0f * direction;
            if (temp_NewPos.y < 0)
            {
                temp_NewPos.y = sf::VideoMode::getDesktopMode().height - 30;
            }
            else if (temp_NewPos.y > sf::VideoMode::getDesktopMode().height)
            {
                temp_NewPos.y = 0;
            }
            if (temp_NewPos.x < 0)
            {
                temp_NewPos.x = sf::VideoMode::getDesktopMode().width - 30;
            }
            else if (temp_NewPos.x > sf::VideoMode::getDesktopMode().width)
            {
                temp_NewPos.x = 0;
            }
            temp_Back->setPosition(temp_NewPos);
            snakeBody.front()->setOutlineThickness(3.0f);
            snakeBody.front()->setOutlineColor(sf::Color::Yellow);

            temp_Back->setOutlineThickness(10.0f);
            temp_Back->setOutlineColor(sf::Color::Red);
            snakeBody.push_front(temp_Back);
            

          

        }
        //Draw Snake
        for (auto it = snakeBody.cbegin(); it != snakeBody.cend(); it++)
        {
            window.draw(**it);
        }
        fWaitTime+= 1.0f* dt;
        fpsText.setString("FPS:" + strFPS);
        window.draw(fpsText);
       // shape.setPosition(sf::Vector2f(0,dy));

        window.display();
    
      
    }

    
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
