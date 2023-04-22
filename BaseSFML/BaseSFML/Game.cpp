#include "Game.h"
void LoadTextureToSprite(const std::string path,Texture& tex, Sprite& sprite, Color a_Color,Vector2f vScale);
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
	auto videoMode = VideoMode::getDesktopMode();
	float temp_xCenter = videoMode.width / 2;
	float temp_yCenter = videoMode.height / 2;
	for (int i = 0; i < 9; i++)
	{
		m_boardArray[i] = GameMove::None;
	}
	if (m_bForceTexture)
	{
		//m_texBG.loadFromFile("graphics/BG.png");
		LoadTextureToSprite("graphics/Bg.png",m_texBG,m_spBG,Color::White,Vector2f(1.0f,1.0f));
		m_spBG.setPosition(0,0);
		
		m_spBG.setScale(videoMode.width/ m_spBG.getLocalBounds().width, videoMode.height / m_spBG.getLocalBounds().height);

		LoadTextureToSprite("graphics/X.png", m_texMainPlayer, m_spMainPlayer, Color::White, Vector2f(0.08f, 0.08f));
		LoadTextureToSprite("graphics/O.png", m_texSecPlayer, m_spSecPlayer, Color::White, Vector2f(0.08f, 0.08f));
		LoadTextureToSprite("graphics/Board.png", m_texBoard, m_spBoard, Color::White, Vector2f(1.4f,1.4f));
		
		//Game Menu Setup
		m_spBoard.setPosition(videoMode.width/3.1f, videoMode.height/3.8f);

		
		m_font.loadFromFile("fonts/KOMIKAP_.ttf");
		m_uiStateText.setFont(m_font);
		m_uiStateText.setPosition(0,0);
		m_uiStateText.setFillColor(Color::Cyan);
		m_uiStateText.setCharacterSize(75);

		
		SetupFont(m_uiPlayerSinglePlayerTxt, m_font,55, temp_xCenter ,
			temp_yCenter / 2 +100,"Single Player");

		SetupFont(m_uiPlayerTwoPLayerTxt, m_font, 55, temp_xCenter ,
			temp_yCenter / 2 + 200 , "Two Player");

		SetupFont(m_uiQuitTxt, m_font, 55, temp_xCenter ,
			temp_yCenter / 2 + 300, "Quit");

	}
	m_MousePointer.setRadius(10);
	m_MousePointer.setFillColor(Color::Green);

	int temp_StartXOffset = 1;
	int temp_Yosset = temp_yCenter*0.48f;
	int temp_Width = 200;
	int temp_Height = 200;
	for (int i=0;i<9;i++)
	{
		m_BoardSquare[i].setSize(sf::Vector2f(temp_Width, temp_Height));
		m_BoardSquare[i].setFillColor(Color(0, 0, 0, 0));
		m_BoardSquare[i].setOutlineColor(sf::Color::Blue);
		m_BoardSquare[i].setOutlineThickness(5);
		
	
			m_BoardSquare[i].setPosition
			(temp_xCenter*0.49f + temp_StartXOffset * temp_Width,
		       temp_Yosset);
			if ((i+1)!=1 && ((i+1) % 3) == 0)
			{
				cout <<endl<< (i+1)<<endl;
				temp_Yosset += temp_Height;
			}
			temp_StartXOffset++;
			if (temp_StartXOffset > 3)
			{
				temp_StartXOffset = 1;
			}
			;
	}
	
	for (int i=0;i<5;i++)
	{
		m_vPoolMainPlayer.push_back(new Sprite(m_spMainPlayer));
		m_vPoolSecondaryPlayer.push_back(new Sprite(m_spSecPlayer));
	}
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

	for (auto const& value : m_vDrawableList)
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
void LoadTextureToSprite(const std::string path,Texture &tex , Sprite &sprite,Color a_Color,Vector2f vScale )
{
	tex.loadFromFile(path);
	sprite.setTexture(tex);
	sprite.setColor(a_Color);
	sprite.setScale(vScale);
}