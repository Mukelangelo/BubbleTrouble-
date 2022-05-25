#pragma once

#include "Controller.h"
#include "Button.h"
#include "macros.h"

constexpr int MENU_BUTTONS = 3;

class Menu
{
public:
	Menu();
	void run(); // run the menu 
	void draw(); 
	void game(); // start the game when pressed 'Start Game'

private:

	// this function will handle clicks on the buttons
	void handleButtons(const sf::Vector2f& location);

	// this function will handle when the mouse hovers over a button.
	void handleHover(const sf::Vector2f& location);  

	// this function is getting events from the user.
	void eventsHandler();

	sf::RenderWindow m_window; 
	sf::String m_texts[MENU_BUTTONS] = { "Start game", "Help", "Exit" };

	Button m_buttons[MENU_BUTTONS]; // menu buttons

	bool m_need_help; // check if 'HELP' is pressed
	bool m_gameOn; // check if 'START GAME' is pressed
	int m_lastHover = 0; // last button hovered over

	sf::RectangleShape m_help_bar;
	sf::Sprite m_bg; // menu background

	
	
};