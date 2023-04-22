#include "Game.h"
void LoadTextureToSprite(const std::string path,Texture& tex, Sprite& sprite);
void SetupFont(Text& text, Font& font, int Size, float x, float y, const string textToDisplay);
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

		float temp_xCenter = videoMode.width / 2;
		float temp_yCenter = videoMode.height / 2;
		SetupFont(m_uiPlayerSinglePlayerTxt, m_font,55, temp_xCenter ,
			temp_yCenter / 2 +100,"Single Player");

		SetupFont(m_uiPlayerTwoPLayerTxt, m_font, 55, temp_xCenter ,
			temp_yCenter / 2 + 200 , "Two Player");

		SetupFont(m_uiQuitTxt, m_font, 55, temp_xCenter ,
			temp_yCenter / 2 + 300, "Quit");

	}
	m_MousePointer.setRadius(10);
	m_MousePointer.setFillColor(Color::Green);

	ChangeState(MainMenu);
}

void SetupFont(Text &text ,Font &font, int Size,float x , float y,const string textToDisplay)
{

	text.setFont(font);
	text.setOrigin(text.getGlobalBounds().width/2, text.getGlobalBounds().height/2);
	text.setPosition(x, y);
	text.setCharacterSize(Size);
	text.setString(textToDisplay);
	text.setOutlineThickness(1.8f);
	text.setOutlineColor(Color::Black);
	text.setFillColor(Color::Green);
}

void Game::Draw(RenderWindow& window)
{
	window.draw(m_spBG);
	for (auto const& value : m_vDrawableTextList)
	{
		window.draw(*value);
	}
	window.draw(m_uiStateText);
	window.draw(m_MousePointer);
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