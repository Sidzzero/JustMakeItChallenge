#include "Game.h"

void Game::Update(RenderWindow& window)
{
	if (Keyboard::isKeyPressed(Keyboard::Num2))
	{
		m_eMenu = Menu::GameMenu;
	}
	else if (Keyboard::isKeyPressed(Keyboard::Num1))
	{
		m_eMenu = Menu::MainMenu;
	}
	switch (m_eMenu)
	{
	case MainMenu:
		m_spBG.setColor(Color::White);
		m_uiStateText.setString("Main Menu");
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

	
	Draw(window);
}
