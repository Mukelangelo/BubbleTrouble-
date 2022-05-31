#include "Resources.h"

Resources::Resources()
{
	loadTextures();
	loadBuffers();
	loadBackground();
	m_font.loadFromFile("font.ttf");
	setPauseScreen();
}

//=======================================================================================
Resources::~Resources() {}

//=======================================================================================
Resources& Resources::instance()
{
	static Resources inst;
	return inst;
}

//=======================================================================================
void Resources::setPauseScreen()
{
	m_pauseWindow.setFillColor(sf::Color(179, 218, 255, 255));
	m_pauseWindow.setPosition(sf::Vector2f(600, 250));
	m_pauseWindow.setSize(sf::Vector2f(340, 230));
	m_pauseWindow.setOutlineThickness(3);
	m_pauseWindow.setOutlineColor(sf::Color::Black);
	auto buttonSize = sf::Vector2f(30, 30);
	auto buttonPos = sf::Vector2f(550, 450);

	m_pauseText.setFont(m_font);
	m_pauseText.setString("Pause");
	m_pauseText.Bold;
	m_pauseText.setOutlineColor(sf::Color(12, 36, 97, 255));
	m_pauseText.setOutlineThickness(3);
	m_pauseText.setCharacterSize(80);
	m_pauseText.setColor(sf::Color(29, 209, 161, 255));
	m_pauseText.setPosition(sf::Vector2f(660, 260));
	SetButtons();
}

//=======================================================================================
void Resources::SetButtons()
{
	for (int i = 0; i < MENU_BUTTONS; i++)
	{
		m_pauseButtons[i].setTexture(&m_pauseTextures[i]);
		m_pauseButtons[i].setSize(sf::Vector2f(90, 90));
		m_pauseButtons[i].setPosition(sf::Vector2f(620 + i * 100, 380));
	}
	m_pauseButtons[MUSIC].setOutlineThickness(4);
	m_pauseButtons[MUSIC].setOutlineColor(sf::Color::Green);
}

//=======================================================================================
void Resources::loadTextures()
{
	for (int i = 0; i < NUM_OF_PICS; i++)
		m_textures[i].loadFromFile(objectTextures[i]);

	for (int i = 0; i < MENU_BUTTONS; i++)
		m_pauseTextures[i].loadFromFile(buttonTextures[i]);
}

//=======================================================================================
sf::Texture* Resources::getTexture(int index)
{
	return &m_textures[index];
}

//=======================================================================================
sf::Texture* Resources::getBackground(int index)
{
	return &m_bg[index];
}

//=======================================================================================
sf::RectangleShape* Resources::getPauseButtons(int index)
{
	return &m_pauseButtons[index];
}

//=======================================================================================
void Resources::loadBackground()
{
	auto loadPic = sf::Texture();
	loadPic.loadFromFile("menu-background.jpg");
	m_bg.push_back(loadPic);

	//loadPic.loadFromFile("help.png");
	//m_bg.push_back(loadPic);

	//loadPic.loadFromFile("bg.png");
	//m_bg.push_back(loadPic);
}

//=======================================================================================
void Resources::loadBuffers()
{

}

//=======================================================================================
void Resources::playSound(int index)
{

}

//=======================================================================================
void Resources::setVolume()
{

}

//=======================================================================================
void Resources::drawPauseScreen(sf::RenderWindow& window)
{
	window.draw(m_pauseWindow);
	window.draw(m_pauseText);
	for (int i = 0; i < 3; i++)
	{
		window.draw(m_pauseButtons[i]);
	}
}

//=======================================================================================
sf::Font* Resources::getFont()
{
	return &m_font;
}

//=======================================================================================
void Resources::playMusic()
{
	static bool musicOn = false; // check if the music is played.
	if (!musicOn)
	{
		m_music.play();
		musicOn = true;
		return;
	}
	m_music.pause();
	musicOn = false;
}