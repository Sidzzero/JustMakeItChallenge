#include "SnakeGame.h"
SnakeGame::SnakeGame(sf::RenderWindow* win) :Game(win)
{
    Init();
}
void SnakeGame::Init()
{
    
    //UI
    fntUI.loadFromFile("Font/arial.ttf");
	//Snake Setup
    vTextOffset.x = 22;
    vTextOffset.y = 7;
    for (int i = 0; i < 2; i++)
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
   
}

void SnakeGame::draw()
{
    m_window->draw(food);
    int i = 0;
    for (auto it = snakeBody.cbegin(); it != snakeBody.cend(); it++)
    {
        m_window->draw(**it);
        snakeNumber[i]->setPosition((*it)->getPosition() + vTextOffset);
        m_window->draw(*snakeNumber[i]);
        i++;
    }
    fWaitTime += 1.0f * dt;//SHOULD WE PUT IN UPDATE?
}

void SnakeGame::handleInput(sf::Event& event)
{
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
    }
}
void SnakeGame::Cleanup()
{
	
}