#include "SnakeGame.h"
#include <iostream>
SnakeGame::SnakeGame(sf::RenderWindow* win) :Game(win)
{
    state = Menu;
    Init();
}
void SnakeGame::Init()
{
    //UI
    fntUI.loadFromFile("Font/arial.ttf");
    txtCurrentState.setFont(fntUI);
    txtCurrentState.setPosition(sf::Vector2f(sf::VideoMode::getDesktopMode().width / 2,0));
	//Snake Setup
    for (int i = 0; i < snakeBody.size(); i++)
    {
        delete snakeBody[i];
    }
    for (int i = 0; i < snakeNumber.size(); i++)
    {
        delete snakeNumber[i];
    }
    snakeBody.clear();
    snakeNumber.clear();
    vTextOffset.x = 22;
    vTextOffset.y = 7;
    direction = sf::Vector2f(1.0f, 0);
    dir = Right;
    for (int i = 0; i < 4; i++)
    {
        auto temp = new sf::CircleShape(30.0f);
        temp->setPosition(sf::Vector2f(400 - i * (63), 400));
        temp->setOutlineColor(sf::Color::Yellow);
        temp->setOutlineThickness(3.0f);
        temp->setFillColor(sf::Color::Green);
        snakeBody.push_back(temp);

        auto temp_Text = new sf::Text();
        temp_Text->setString(std::to_string(i + 1));
        temp_Text->setFont(fntUI);
        temp_Text->setPosition(temp->getPosition() + vTextOffset);
        temp_Text->setFillColor(sf::Color::Blue);
        snakeNumber.push_back(temp_Text);
    }

    food.setSize(sf::Vector2f(30, 30));
    food.setPosition(sf::VideoMode::getDesktopMode().width / 2, sf::VideoMode::getDesktopMode().height / 2);
    food.setFillColor(sf::Color::Magenta);
}
void SnakeGame::update()
{

    switch (state)
    {
    case Playing:
    
        if (fWaitTime > snakeUpdateTime)
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
        if (snakeBody.front()->getGlobalBounds().intersects(food.getGlobalBounds()) == true)
        {
            sf::Vector2f newFoodPostion;
            newFoodPostion.x = rand() % (sf::VideoMode::getDesktopMode().width - 80);
            newFoodPostion.y = rand() % (sf::VideoMode::getDesktopMode().height - 80);
            food.setPosition(newFoodPostion);
            snakeBody.push_back(new sf::CircleShape(*snakeBody.back()));
            auto temp_Number = new sf::Text(*snakeNumber[0]);
            temp_Number->setString(std::to_string(snakeBody.size()));
            temp_Number->setPosition((snakeBody.back())->getPosition() + vTextOffset);
            snakeNumber.push_back(temp_Number);
        }
        if (CheckCollision())
        {
            state = GameOver;
        }
        break;

    case GameOver:

        break;
    case Paused:
        break;
    case Menu:
        txtCurrentState.setString("Main Menu \n   1.Play \n   2.Exit");

        break;
    default:
        break;
    }

  
   
}

void SnakeGame::draw()
{
    int i = 0;
    switch (state)
    {
    case Playing:
        m_window->draw(food);
      
        for (auto it = snakeBody.cbegin(); it != snakeBody.cend(); it++)
        {
            m_window->draw(**it);
            snakeNumber[i]->setPosition((*it)->getPosition() + vTextOffset);
            m_window->draw(*snakeNumber[i]);
            i++;
        }
        txtCurrentState.setString("Playing \n Press 'p' Pause! \n   2.Exit");
        break;
    case GameOver:
        m_window->draw(food);

        for (auto it = snakeBody.cbegin(); it != snakeBody.cend(); it++)
        {
            m_window->draw(**it);
            snakeNumber[i]->setPosition((*it)->getPosition() + vTextOffset);
            m_window->draw(*snakeNumber[i]);
            i++;
        }
        txtCurrentState.setString("Game Over \n Press 'R' Restart! \n   2.Exit");
        break;
    case Paused:
        m_window->draw(food);

        for (auto it = snakeBody.cbegin(); it != snakeBody.cend(); it++)
        {
            m_window->draw(**it);
            snakeNumber[i]->setPosition((*it)->getPosition() + vTextOffset);
            m_window->draw(*snakeNumber[i]);
            i++;
        }
        txtCurrentState.setString("PAUSED ! \n Press 'p' Unpause! \n   2.Exit");
        break;
    case Menu:
        txtCurrentState.setString("Main Menu \n   1.Play \n   2.Exit");
        break;
    default:
        break;
    }

    fWaitTime += 1.0f * dt;//SHOULD WE PUT IN UPDATE?

    m_window->draw(txtCurrentState);
}

void SnakeGame::handleInput(sf::Event& event)
{
  
        switch (state)
        {
        case Playing:
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Right)
                {
                    if (dir != eDirection::Left)
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
                else  if (event.key.code == sf::Keyboard::P)
                {
                    state = Paused;

                }
                if (event.key.code == sf::Keyboard::Num2)
                {
                    state = Menu;
                    m_window->close();

                }
            }
            break;

        case GameOver:
            if (event.type == sf::Event::KeyPressed)
                if (event.key.code == sf::Keyboard::R)
                {
                    state = Playing;
                    Init();
                }
                else  if (event.key.code == sf::Keyboard::Num2)
                {
                    state = Menu;
                    m_window->close();

                }
            break;
        case Paused:
            if (event.type == sf::Event::KeyPressed)
            if (event.key.code == sf::Keyboard::P)
            {
                state = Playing;
            }
            if (event.key.code == sf::Keyboard::Num2)
            {
                state = Menu;
                m_window->close();

            }
            break;
        case Menu:
            if (event.type == sf::Event::KeyPressed)
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Num1)
                {
                state = Playing;
                Init();

                }
                else if (event.key.code == sf::Keyboard::Num2)
                {
                    state = Menu;
                    m_window->close();

                }
            }
            break;
        default:
            break;

    }
}
void SnakeGame::Cleanup()
{
    
}

bool SnakeGame::CheckCollision()
{
    //Check head with all body parts
    //(body - head) same line and less distance
    for (int i =1; i <snakeBody.size(); i++)
    {
        auto diffVec = (snakeBody[0]->getPosition() - snakeBody[i]->getPosition());
        if (abs( diffVec.x)<62 && abs(diffVec.y)<62)
        {
            return true;
        }
       
    }
    return false;
}