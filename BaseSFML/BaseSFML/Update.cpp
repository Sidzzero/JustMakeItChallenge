#include "Game.h"

void Game::Update(RenderWindow& window)
{
	switch (m_eMenu)
	{
	case MainMenu:
		break;
	case GameMenu:
		break;
	default:
		cout << "Invalid Menu !"<<endl;
		break;
	}
	//Logics above


	Draw(window);
}
