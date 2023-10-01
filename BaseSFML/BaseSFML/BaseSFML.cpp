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

    auto screenHeight = sf::VideoMode::getDesktopMode().height;
    auto screenWidth = sf::VideoMode::getDesktopMode().width;

    //FPS calculations...
    sf::Font fpsFont;
    sf::Text fpsText;
    fpsFont.loadFromFile("Font/arial.ttf");
    std::cout << "FontInfo:" + fpsFont.getInfo().family;
    fpsText.setFont(fpsFont);
    fpsText.setString("FPS:over 9000");
    fpsText.setFillColor(sf::Color::White);

    float dt;
    sf::Clock clock;
    std::string strFPS;
    float dy = 0;

    //Body parts
    sf::CircleShape shape(30.0f);
    shape.setFillColor(sf::Color::Green);
    std::deque<sf::CircleShape*> snakeBody;
    sf::Vector2f direction = sf::Vector2f(1.0f, 0.0f);
    eDirection dir = eDirection::Right;
    //Snake Number
    std::vector<sf::Text*> snakeNumber;
    sf::Vector2f vTextOffset;
    vTextOffset.x = 22;
    vTextOffset.y = 7;
    for (int i=0;i<2;i++)
    {
        auto temp = new sf::CircleShape(30.0f);
        temp->setPosition(sf::Vector2f(400 - i*(63), 400));
        temp->setOutlineColor(sf::Color::Yellow);
        temp->setOutlineThickness(3.0f);
        temp->setFillColor(sf::Color::Green);
        snakeBody.push_back(temp) ;

        auto temp_Text = new sf::Text(fpsText);
        temp_Text->setString(std::to_string(i+1));
        temp_Text->setPosition( temp->getPosition() + vTextOffset) ;
        temp_Text->setFillColor(sf::Color::Blue);
        snakeNumber.push_back(temp_Text);
    }



    float fWaitTime = 0.0f;
    float snakeUpdateTime = 0.25f;

    //FOOD
    sf::RectangleShape food;
    food.setSize(sf::Vector2f(30,30));
    food.setPosition(screenWidth/2,screenHeight/2);
    food.setFillColor(sf::Color::Magenta);

    

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
     
        if (snakeBody.front()->getGlobalBounds().intersects(food.getGlobalBounds()) == true)
        {
            sf::Vector2f newFoodPostion;
            newFoodPostion.x = rand() % (screenWidth - 80);
            newFoodPostion.y = rand() % (screenHeight- 80);
            food.setPosition(newFoodPostion);
            snakeBody.push_back(new sf::CircleShape(*snakeBody.back() ) );
            auto temp_Number = new sf::Text(*snakeNumber[0]);
            temp_Number->setString(std::to_string(snakeBody.size()));
            temp_Number->setPosition((snakeBody.back())->getPosition()  +vTextOffset);
            snakeNumber.push_back(temp_Number);
        }
        

        //Snake Update Below
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
        window.draw(food);
        //Draw Snake
        int i = 0;
        for (auto it = snakeBody.cbegin(); it != snakeBody.cend(); it++)
        {
            window.draw(**it);
            snakeNumber[i]->setPosition((*it)->getPosition() + vTextOffset);
            window.draw(*snakeNumber[i]);
            i++;
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
