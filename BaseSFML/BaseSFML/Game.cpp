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
		auto videoMode = VideoMode::getDesktopMode();
		m_spBG.setScale(videoMode.width/ m_spBG.getLocalBounds().width, videoMode.height / m_spBG.getLocalBounds().height);

		LoadTextureToSprite("graphics/X.png", m_texMainPlayer, m_spMainPlayer);
		LoadTextureToSprite("graphics/O.png", m_texSecPlayer, m_spSecPlayer);
		LoadTextureToSprite("graphics/Board.png", m_texBoard, m_spBoard);
		m_font.loadFromFile("fonts/KOMIKAP_.ttf");
		m_uiStateText.setFont(m_font);
		m_uiStateText.setPosition(0,0);
		m_uiStateText.setFillColor(Color::Cyan);
		m_uiStateText.setCharacterSize(75);
	}
}



void Game::Draw(RenderWindow& window)
{
	window.draw(m_spBG);
	window.draw(m_uiStateText);
}

void Game::Input(RenderWindow& window)
{
}

void Game::Cleanup()
{
}
void LoadTextureToSprite(const std::string path,Texture &tex , Sprite &sprite )
{
	tex.loadFromFile(path);
	sprite.setTexture(tex);
}