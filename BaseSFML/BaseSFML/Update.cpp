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

	for (auto value: m_vMainPlayer)
	{
		m_vPoolMainPlayer.push_back(value);
	}
	for (auto value : m_vSecondaryPlayer)
	{
		m_vPoolSecondaryPlayer.push_back(value);
	}
	switch (a_NewMenuState)
	{
	case MainMenu:
		m_vDrawableTextList.push_back(&m_uiPlayerSinglePlayerTxt);
		m_vDrawableTextList.push_back(&m_uiPlayerTwoPLayerTxt);
		m_vDrawableTextList.push_back(&m_uiQuitTxt);
		m_uiStateText.setString("Main Menu");
		m_spBG.setColor(Color::White);
		
		m_eMenu = Menu::MainMenu;
		m_eState = GameState::Playing;
		m_eGameType = GameType::PvAI;
		break;
	case GameMenu:
		m_iTurnCount = 1;
		m_eMenu = Menu::MainMenu;
		m_eState = GameState::Playing;

		for (int i = 0; i < 9; i++)
		{
			m_boardArray[i] = GameMove::None;
		}
		m_uiStateText.setString("Game Menu");
		m_spBG.setColor(Color::Green);
		m_uiTurnText.setString("Press Enter to Start");
		m_uiTurnText.setFillColor(Color::White);
		m_iTurn = GameMove::None;
		m_vDrawableTextList.push_back(&m_uiTurnText);
	
		for(int i=0;i<9;i++)
		m_vDrawableList.push_back(&m_BoardSquare[i]);

		break;
	default:
		break;
	}
	m_eMenu = a_NewMenuState;
}
void Game::ChangeGameState(GameState a_GameState)
{
	switch (a_GameState)
	{
	case Playing:
		break;
	case Win:
		m_vDrawableTextList.push_back(&m_uiGameStatus);
		m_vDrawableTextList.push_back(&m_uiPlayAgain);
		m_vDrawableTextList.push_back(&m_uiMainMenu);
		m_vDrawableList.push_back(&m_BGForHide);
		break;
	case GameState::Draw:
		m_vDrawableTextList.push_back(&m_uiGameStatus);
		m_vDrawableTextList.push_back(&m_uiPlayAgain);
		m_vDrawableTextList.push_back(&m_uiMainMenu);
		m_vDrawableList.push_back(&m_BGForHide);
		break;
	case Paused:
		break;
	default:
		break;
	}
	m_eState = a_GameState;
}
void Game::ChangeTurn()
{
	if (m_iTurn== GameMove::None)
	{
		cout<< endl << "Exception :Game not started!"<<endl;
		m_uiStateText.setString("Press Enter to Start");
	}

	if (m_iTurn == GameMove::X)
	{
		m_vMainPlayer.push_back(m_vPoolMainPlayer.back());
		m_vDrawableList.push_back(m_vPoolMainPlayer.back());
		m_vPoolMainPlayer.pop_back();
		m_iTurn = GameMove::O;
		m_uiTurnText.setString("O's turn");
		m_uiTurnText.setFillColor(Color::Red);
	}
	else if (m_iTurn == GameMove::O)
	{
		m_vSecondaryPlayer.push_back(m_vPoolSecondaryPlayer.back());
		m_vDrawableList.push_back(m_vPoolSecondaryPlayer.back());
		m_vPoolSecondaryPlayer.pop_back();
		m_iTurn = GameMove::X;
		m_uiTurnText.setString("X's turn");
		m_uiTurnText.setFillColor(Color::Green);
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
			if (Keyboard::isKeyPressed(Keyboard::Return) && m_iTurn == GameMove::None)
			{
				m_iTurn = GameMove::X;
				m_uiTurnText.setString("X's turn");
				m_uiTurnText.setFillColor(Color::Green);
				
			}
			else if (Mouse::isButtonPressed(Mouse::Left))
			{
		       if(m_iTurn != GameMove::None)
				for (int i=0;i<9;i++)
				{
					if (m_BoardSquare[i].getGlobalBounds().contains(Vector2f(temp_mousePos)) &&
						m_boardArray[i] == GameMove::None)
					{
						m_boardArray[i] = m_iTurn;
						if (m_iTurn == GameMove::X)
						{
							m_vPoolMainPlayer.back()->setPosition
							(m_BoardSquare[i].getGlobalBounds().left,
								m_BoardSquare[i].getGlobalBounds().top);
							m_iTurnCount++;
						}
						else if (m_iTurn == GameMove::O)
						{
							m_vPoolSecondaryPlayer.back()->setPosition
							    (m_BoardSquare[i].getGlobalBounds().left,
								m_BoardSquare[i].getGlobalBounds().top);
							m_iTurnCount++;
						}
						auto Result = CheckWinner();
						if (Result != GameMove::None)
						{
							m_uiTurnText.setString("Turn Completed So Far !"+m_iTurnCount);
							m_uiTurnText.setFillColor(Color::White);
							auto temp_WinnerMsg = "Game Over ! Winner is X";
							if (Result == GameMove::O)
							{
								auto temp_WinnerMsg = "Game Over ! Winner is O";
							}
							m_uiGameStatus.setString(temp_WinnerMsg);
							ChangeGameState(GameState::Win);
						}
						else
						{
							ChangeTurn();
						}
						break;
					}
					else if (m_iTurnCount >9)
					{
						m_uiTurnText.setString("All Turns Complete !");
						m_uiTurnText.setFillColor(Color::White);
						m_uiGameStatus.setString("Game Over !\n DRAW the Match!");
						ChangeGameState(GameState::Draw);
					}
				}
			}

			

		}
		else if(m_eState == GameState::Paused)
		{
			//TODO
		}
		else
		{
			if (DetectTextCollision(
				m_MousePointer.getGlobalBounds(),
				Color::Black, Color::White,
				m_uiMainMenu
			))
			{
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					ChangeState(MainMenu);
				}

			}
			else if (DetectTextCollision(
				m_MousePointer.getGlobalBounds(),
				Color::Black, Color::White,
				m_uiPlayAgain
			))
			{
				if (Mouse::isButtonPressed(Mouse::Left))
				{
					ChangeState(Menu::GameMenu);
				}
			}
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

GameMove Game::CheckWinner()
{
	for (int i=0;i<3;i++)
	{
		if (m_boardArray[i + 2 * i] == m_boardArray[i+1 + 2 * i] &&
			m_boardArray[i + 1 + 2 * i] == m_boardArray[i + 2 + 2 * i]&&
			m_boardArray[i + 2 + 2 * i] == m_boardArray[i + 2 * i])
		{
			if (m_boardArray[i + 2 * i] == 1)
			{
				return GameMove::X;
			}
			else if (m_boardArray[i + 2 * i] == 2)
			{
				return GameMove::O;
			}
		}
		if (m_boardArray[i] == m_boardArray[3 +i] &&
			m_boardArray[3+i] == m_boardArray[6+i] &&
			m_boardArray[6+i] == m_boardArray[0+i])
		{
			if (m_boardArray[i] == 1)
			{
				return GameMove::X;
			}
			else if (m_boardArray[i] == 2)
			{
				return GameMove::O;
			}
		}
	}

	
	//Diagonal
	if (m_boardArray[0] == m_boardArray[4]  &&
		m_boardArray[4]==m_boardArray[8] &&
		m_boardArray[8] == m_boardArray[0])
	{
		if (m_boardArray[0] == 1)
		{
			return GameMove::X;
		}
		else if (m_boardArray[0] == 2)
		{
			return GameMove::O;
		}
	}
	if (m_boardArray[2] == m_boardArray[4] &&
		m_boardArray[4]  ==m_boardArray[6]&&
		m_boardArray[6] == m_boardArray[2])
	{
		if (m_boardArray[2] == 1)
		{
			return GameMove::X;
		}
		else if (m_boardArray[2] == 2)
		{
			return GameMove::O;
		}
	}
	return GameMove::None;
}

