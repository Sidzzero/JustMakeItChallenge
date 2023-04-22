#include "Game.h"
bool DetectTextCollision(const FloatRect MousePos ,Color OldColor ,Color NewColor,sf::Text &text )
{
	if (MousePos.intersects(text.getGlobalBounds()))
	{
		text.setOutlineColor(NewColor);
		return true;
	}
	else
	{
		text.setOutlineColor(OldColor);
		return false;
	}
}

void Game::ChangeState(Menu a_NewMenuState)
{
	m_vDrawableTextList.clear();
	switch (a_NewMenuState)
	{
	case MainMenu:
		m_vDrawableTextList.push_back(&m_uiPlayerSinglePlayerTxt);
		m_vDrawableTextList.push_back(&m_uiPlayerTwoPLayerTxt);
		m_vDrawableTextList.push_back(&m_uiQuitTxt);
		m_uiStateText.setString("Main Menu");
		m_spBG.setColor(Color::White);
		
		break;
	case GameMenu:
		m_uiStateText.setString("Game Menu");
		m_spBG.setColor(Color::Green);
		m_vDrawableSpriteList.push_back(&m_spMainPlayer);
		m_vDrawableSpriteList.push_back(&m_spSecPlayer);
		m_vDrawableSpriteList.push_back(&m_spBoard);

		break;
	default:
		break;
	}
	m_eMenu = a_NewMenuState;
}
void Game::Update(RenderWindow& window)
{
	if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		//m_eMenu = Menu::GameMenu;
		ChangeState(Menu::GameMenu);
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		m_eMenu = Menu::MainMenu;
		ChangeState(Menu::MainMenu);
	}
	switch (m_eMenu)
	{
	case MainMenu:
		//----Collision Check------
    //Text Collision
	{
		
		if (DetectTextCollision(
			m_MousePointer.getGlobalBounds(),
			Color::Black, Color::White,
			m_uiPlayerSinglePlayerTxt
		))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				ChangeState(GameMenu);
			}

		}
		else if (DetectTextCollision(
			m_MousePointer.getGlobalBounds(),
			Color::Black, Color::White,
			m_uiPlayerTwoPLayerTxt
		))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				ChangeState(GameMenu);
			}
		}
		else if (DetectTextCollision(
			m_MousePointer.getGlobalBounds(),
			Color::Black, Color::White,
			m_uiQuitTxt
		))
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				window.close();
			}
		}
	}
		
		//----End of Collision Check
		break;
	case GameMenu:
		
	
		break;
	default:
		cout << "Invalid Menu !"<<endl;
		break;
	}
	//Logics above

	//Mouse
	auto temp_MousePos = Mouse::getPosition();
	m_MousePointer.setPosition(temp_MousePos.x, temp_MousePos.y);


	Draw(window);
}
