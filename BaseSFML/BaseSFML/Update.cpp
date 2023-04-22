#include "Game.h"
void Game::ChangeState(Menu a_NewMenuState)
{
	m_vDrawableTextList.clear();
	switch (a_NewMenuState)
	{
	case MainMenu:
		m_vDrawableTextList.push_back(m_uiPlayerSinglePlayerTxt);
		m_vDrawableTextList.push_back(m_uiPlayerTwoPLayerTxt);
		m_vDrawableTextList.push_back(m_uiQuitTxt);
		break;
	case GameMenu:


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
		m_spBG.setColor(Color::White);
		m_uiStateText.setString("Main Menu");

		//----Collision Check
		
		//----End of Collision Check
		break;
	case GameMenu:
		m_spBG.setColor(Color::Green);
		m_uiStateText.setString("Game Menu");
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
