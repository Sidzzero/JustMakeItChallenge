#pragma once
#include <iostream>
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

	//GRahpics
	sf::Texture m_texBG;
	sf::Texture m_texMainPlayer;
	sf::Texture m_texSecPlayer;
	sf::Texture m_texBoard;

	sf::Sprite m_spBG;
	sf::Sprite m_spMainPlayer;
	sf::Sprite m_spSecPlayer;
	sf::Sprite m_spBoard;

};

