#include "PreCompile.h"
#include "GUI.h"
using namespace Gui;

//Constructor/Destructor

DropDownList::DropDownList(float x, float y, float w, float h, sf::Font& font, std::string list[], int numberOfElements, int default_index)
	:font(font)
{
	//unsigned numberOfElements = sizeof(list) / sizeof(std::string);
	this->showList = false;

	this->keyTimeMax = 10.f;
	this->keyTime = this->keyTimeMax;

	this->activeElement = new Button(
		x, y, w, h, &this->font,
		list[default_index], 20,
		sf::Color(255, 255, 255, 200), sf::Color(255, 255, 255, 255), sf::Color(250, 250, 20, 255),
		sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200),
		sf::Color(255, 255, 255, 200), sf::Color(150, 150, 150, 200), sf::Color(20, 20, 20, 200));

	for (int i = 0; i < numberOfElements; ++i)
	{
		this->list.push_back(
			new Button(x, y + (i + 1) * h, w, h, &this->font,
				list[i], 20,
				sf::Color(255, 255, 255, 150), sf::Color(255, 255, 255, 255), sf::Color(250, 250, 20, 255),
				sf::Color(70, 70, 70, 200), sf::Color(150, 150, 150, 255), sf::Color(20, 20, 20, 200),
				sf::Color(255, 255, 255, 0), sf::Color(255, 255, 255, 0), sf::Color(250, 250, 20, 0),
				i)
		);
	}

}

DropDownList::~DropDownList()
{
	if (activeElement)
	{
		delete this->activeElement;
	}

	for (auto& bt : list)
	{
		if (bt)
		{
			delete bt;
		}
	}
}

//Accessors

const unsigned short& Gui::DropDownList::getActiveElementId() const
{
	return this->activeElement->getId();
}

//Functions

const bool DropDownList::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0;
		return true;
	}

	return false;
}

void DropDownList::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 50.f * dt;
	}
}

void DropDownList::update(const sf::Vector2f& mousePos, const float& dt)
{
	this->activeElement->update(mousePos);
	this->updateKeyTime(dt);

	//Show and hide the drop-down list
	if (this->activeElement->isPressed() && this->getKeyTime())
	{
		if (this->showList) { this->showList = false; }
		else { this->showList = true; }
	}

	if (this->showList)
	{
		for (auto& i : this->list)
		{
			i->update(mousePos);

			if (i->isPressed())
			{
				this->showList = false;
				this->activeElement->setText(i->getText());
				this->activeElement->setId(i->getId());
			}
		}
	}
}

void DropDownList::render(sf::RenderTarget& target)
{
	this->activeElement->render(target);

	if (showList)
	{
		for (auto& i : this->list)
		{
			i->render(target);
		}
	}
}