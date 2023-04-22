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
	m_vDrawableList.clear();
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
		m_vDrawableList.push_back(&m_spMainPlayer);
		m_vDrawableList.push_back(&m_spSecPlayer);
		//m_vDrawableSpriteList.push_back(&m_spBoard);
		for(int i=0;i<9;i++)
		m_vDrawableList.push_back(&m_BoardSquare[i]);

		break;
	default:
		break;
	}
	m_eMenu = a_NewMenuState;
}
void Game::ChangeTurn()
{
	if (m_iTurn== GameMove::None)
	{
		throw "Exception :Game not started!";
	}
	if (m_iTurn == GameMove::X)
	{
		m_iTurn = GameMove::O;
	}
	else if (m_iTurn == GameMove::O)
	{
		m_iTurn = GameMove::X;
	}
}
void Game::Update(RenderWindow& window)
{
	auto temp_mousePos = Mouse::getPosition();
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
	else if (Keyboard::isKeyPressed(Keyboard::Num3))
	{
		if (m_iTurn == GameMove::X)
		{
			m_iTurn = GameMove::O;
		}
		else if(m_iTurn == GameMove::O)
		{
			m_iTurn = GameMove::X;
		}
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
		//TODO:Switch player here
		if (m_eState == GameState::Playing)
		{
			if (Mouse::isButtonPressed(Mouse::Left))
			{
				//m_spMainPlayer.setPosition(temp_mousePos.x,temp_mousePos.y);
				//auto temp_OneUnit= m_spBoard.getGlobalBounds().left+ m_spBoard.getGlobalBounds().width/3.0f;
				//m_spMainPlayer.setPosition(temp_OneUnit, temp_mousePos.y);
				for (int i=0;i<9;i++)
				{
					if (m_BoardSquare[i].getGlobalBounds().contains(Vector2f(temp_mousePos)) &&
						m_boardArray[i] == GameMove::None)
					{
						m_spMainPlayer.setPosition(
							m_BoardSquare[i].getGlobalBounds().left,
							m_BoardSquare[i].getGlobalBounds().top);
						m_boardArray[i] = m_iTurn;
						ChangeTurn();
						break;
					}
				}
			}


		}
		else
		{

		}
	
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
