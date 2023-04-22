#pragma once
#include <iostream>
#include <vector>
#include "SFML/Graphics.hpp"
using namespace std;
using namespace sf;

enum Menu
{
	MainMenu,
	GameMenu
};
enum GameState
{
	Playing,
	Win,
	Lose,
	Draw,
	Paused
};
enum GameType
{
	PvAI,
	PvP,
};
enum GameMove
{
	None = 0,
	X = 1,
	O = 2
};
class Game
{
public:
	Game();

	void Init(bool m_bForceTexture);
	void Update(RenderWindow& window);

	void Cleanup();


private:
	Menu m_eMenu;
	GameState m_eState;
	GameType m_eGameType;
	void Draw(RenderWindow& window);
	void Input(RenderWindow& window);
	void ChangeState(Menu a_NewMenuState);
	void ChangeGameState(GameState a_GameState);
	sf::RectangleShape m_BGForHide;
	//GRahpics
	sf::Texture m_texBG;
	sf::Texture m_texMainPlayer;
	sf::Texture m_texSecPlayer;
	sf::Texture m_texBoard;

	sf::Sprite m_spBG;
	sf::Sprite m_spMainPlayer;
	sf::Sprite m_spSecPlayer;
	sf::Sprite m_spBoard;

	vector<Sprite*> m_vMainPlayer;
	vector<Sprite*> m_vSecondaryPlayer;

	vector<Sprite*> m_vPoolMainPlayer;
	vector<Sprite*> m_vPoolSecondaryPlayer;

	Font m_font;
	Text m_uiStateText;
	sf::CircleShape m_MousePointer;

	//Main Menu
	Text m_uiPlayerSinglePlayerTxt;
	Text m_uiPlayerTwoPLayerTxt;
	Text m_uiQuitTxt;
	
	//Game Menu
	Text m_uiTurnText;
	Text m_uiGameStatus;
	Text m_uiPlayAgain;
	Text m_uiMainMenu;
	void ChangeTurn();

	GameMove CheckWinner();
	GameMove m_iTurn = GameMove::X;
	GameMove m_iAITurn = GameMove::O;
	vector<int> m_vREmainingPlace;
	int m_iTurnCount = 0;
	sf::RectangleShape m_BoardSquare[9];

	vector<Text*> m_vDrawableTextList;
	
	vector<Drawable*> m_vDrawableList;
	int m_boardArray[9] = {
		                   0,0,0,
						   0,0,0,
	                       0,0,0};


};

