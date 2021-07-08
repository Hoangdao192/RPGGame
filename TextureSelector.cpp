#include "PreCompile.h"
#include "GUI.h"

using namespace Gui;

//Constructor/Destructor

TextureSelector::TextureSelector(float x, float y, float width, float height, float gridSize, const sf::Texture* texture_sheet, sf::Font& font)
{
	this->keyTime = 0;
	this->keyTimeMax = 10;

	this->active = false;
	this->gridSize = gridSize;
	this->hidden = false;

	float offset = 100;

	this->bounds.setSize(sf::Vector2f(width, height));
	this->bounds.setPosition(x + offset, y);
	this->bounds.setFillColor(sf::Color(50, 50, 50, 100));
	this->bounds.setOutlineThickness(1.f);
	this->bounds.setOutlineColor(sf::Color(255, 255, 255, 200));

	this->sheet.setTexture(*texture_sheet);
	this->sheet.setPosition(x + offset, y);

	//Set the texture inside the bounds box
	if (this->sheet.getGlobalBounds().width > this->bounds.getGlobalBounds().width)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, (int)this->bounds.getGlobalBounds().width, (int)this->sheet.getGlobalBounds().height));
	}

	if (this->sheet.getGlobalBounds().height > this->bounds.getGlobalBounds().height)
	{
		this->sheet.setTextureRect(sf::IntRect(0, 0, (int)this->sheet.getGlobalBounds().width, (int)this->bounds.getGlobalBounds().height));
	}

	this->selector.setPosition(x, y);
	this->selector.setSize(sf::Vector2f(gridSize, gridSize));
	this->selector.setFillColor(sf::Color::Transparent);
	this->selector.setOutlineThickness(1);
	this->selector.setOutlineColor(sf::Color::Red);

	this->textureRect.width = (int)gridSize;
	this->textureRect.height = (int)gridSize;

	this->hideButton = new Button(x, y, 80, 80, &font,
		"Texture\nSelector", 18,
		sf::Color(255, 255, 255, 255),
		sf::Color(0, 255, 255, 255),
		sf::Color(250, 250, 20, 255),
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

TextureSelector::~TextureSelector()
{
	if (this->hideButton) { delete this->hideButton; }
}

//Accessors

const bool& Gui::TextureSelector::getActive() const
{
	return this->active;
}

const sf::IntRect& Gui::TextureSelector::getTextureRect() const
{
	return this->textureRect;
}

const bool Gui::TextureSelector::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0;
		return true;
	}

	return false;
}

//Functions

void Gui::TextureSelector::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 50.f * dt;
	}
}

void Gui::TextureSelector::update(const sf::Vector2i& mousePosWindow, const float& dt)
{
	this->updateKeyTime(dt);

	this->hideButton->update((sf::Vector2f)mousePosWindow);

	if (this->hideButton->isPressed() && this->getKeyTime())
	{
		if (this->hidden) { this->hidden = false; }
		else { this->hidden = true; }
	}

	if (!this->hidden)
	{
		if (this->bounds.getGlobalBounds().contains((sf::Vector2f)mousePosWindow)) { this->active = true; }
		else { this->active = false; }

		if (this->active)
		{
			this->mousePosGrid.x = ((mousePosWindow.x - (int)this->bounds.getPosition().x) / (int)this->gridSize);
			this->mousePosGrid.y = ((mousePosWindow.y - (int)this->bounds.getPosition().y) / (int)this->gridSize);

			this->selector.setPosition(
				this->bounds.getPosition().x + this->mousePosGrid.x * this->gridSize,
				this->bounds.getPosition().y + this->mousePosGrid.y * this->gridSize
			);

			//Update texture rectangle
			this->textureRect.left = (int)this->selector.getPosition().x - (int)this->bounds.getPosition().x;
			this->textureRect.top = (int)this->selector.getPosition().y - (int)this->bounds.getPosition().y;
		}
	}
}

void Gui::TextureSelector::render(sf::RenderTarget& target)
{
	this->hideButton->render(target);
	if (!this->hidden)
	{
		target.draw(this->bounds);
		target.draw(this->sheet);
		target.draw(this->selector);
	}
}
