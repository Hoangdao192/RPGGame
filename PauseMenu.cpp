#include "PreCompile.h"
#include "PauseMenu.h"

//Constructor/Destructor

PauseMenu::PauseMenu(sf::RenderWindow& window, sf::Font& font)
	:font(font)
{
	//Init background
	this->background.setSize((sf::Vector2f)window.getSize());
	this->background.setFillColor(sf::Color(20, 20, 20, 100));

	//Init container
	sf::Vector2f window_size = (sf::Vector2f)window.getSize();
	window_size.x /= 4.f;
	window_size.y -= 60.f;
	this->container.setSize(window_size);
	this->container.setFillColor(sf::Color(20, 20, 20, 200));
	this->container.setPosition(((float)window.getSize().x - this->container.getSize().x) / 2.f, 30.f);

	//Init text
	this->menuText.setFont(font);
	this->menuText.setFillColor(sf::Color(255, 255, 255, 200));
	this->menuText.setCharacterSize(40);
	this->menuText.setString("PAUSED");
	sf::Vector2f center_text = this->container.getPosition();
	center_text.x += (this->container.getGlobalBounds().width - this->menuText.getGlobalBounds().width) / 2;
	center_text.y += 20.f;
	this->menuText.setPosition(center_text);


}

PauseMenu::~PauseMenu()
{
	std::map<std::string, Button*>::iterator it = buttons.begin();
	for (; it != buttons.end(); ++it)
	{
		delete it->second;
	}
	buttons.clear();
}

std::map<std::string, Button*>& PauseMenu::getButtons()
{
	return this->buttons;
}

//Functions

const bool PauseMenu::isButtonPressed(const std::string key)
{
	return this->buttons[key]->isPressed();
}

void PauseMenu::addButton(const std::string key, float y, const std::string text)
{
	float width = 150;
	float height = 50;
	float x = this->container.getPosition().x + (this->container.getGlobalBounds().width - width) / 2;
	this->buttons[key] = new Button(x, y, width, height, &this->font,
		text, 20,
		sf::Color(255, 255, 255, 200),
		sf::Color(0, 255, 255, 255),
		sf::Color(250, 250, 20, 255),
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

void PauseMenu::update(const sf::Vector2i& mousePos )
{
	for (auto& bt : this->buttons)
	{
		bt.second->update((sf::Vector2f)mousePos);
	}
}

void PauseMenu::render(sf::RenderTarget& target)
{
	target.draw(this->background);
	target.draw(this->container);
	for (auto& it : this->buttons)
	{
		it.second->render(target);
	}

	target.draw(this->menuText);
}