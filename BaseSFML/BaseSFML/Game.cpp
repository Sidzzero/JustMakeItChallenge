#include "Game.h"
void LoadTextureToSprite(const std::string path,Texture& tex, Sprite& sprite);

Game::Game()
{
	Init(true);
}

void Game::Init(bool m_bForceTexture)
{
	m_eMenu = Menu::MainMenu;
	m_eState = GameState::Playing;
	m_eGameType = GameType::PvAI;
	if (m_bForceTexture)
	{
		//m_texBG.loadFromFile("graphics/BG.png");
		LoadTextureToSprite("graphics/Bg.png",m_texBG,m_spBG);
		m_spBG.setPosition(0,0);
	}
}



void Game::Draw(RenderWindow& window)
{
	window.draw(m_spBG);
}

void Game::Cleanup()
{
}
void LoadTextureToSprite(const std::string path,Texture &tex , Sprite &sprite )
{
	tex.loadFromFile(path);
	sprite.setTexture(tex);
}