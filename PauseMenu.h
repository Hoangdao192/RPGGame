#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include "GUI.h"

using namespace Gui;

class PauseMenu
{
private:

	//Variables
	sf::Font& font;
	sf::Text menuText;
	sf::RectangleShape background;
	sf::RectangleShape container;

	std::map<std::string, Button*> buttons;

public:
	PauseMenu(sf::RenderWindow& window, sf::Font& font);
	virtual ~PauseMenu();

	//Accessor
	std::map<std::string, Button*>& getButtons();

	//Functions
	const bool isButtonPressed(const std::string key);
	void addButton(const std::string key, float y, const std::string text);
	void update(const sf::Vector2i& mousePos);
	void render(sf::RenderTarget& target);
};

#endif // !PAUSEMENU_H
