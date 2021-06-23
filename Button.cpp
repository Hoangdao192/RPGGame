#include "PreCompile.h"
#include "GUI.h"
using namespace Gui;

Button::Button(float x, float y, float width, float height,
	sf::Font* font,	std::string text, unsigned character_size,
	sf::Color text_idle_color, sf::Color text_hover_color, sf::Color text_active_color,
	sf::Color idle_color, sf::Color hover_color, sf::Color active_color, 
	sf::Color outline_idle_color, sf::Color outline_hover_color, sf::Color outline_active_color,
	short unsigned id)
{
	this->buttonState = BTN_IDLE;

	this->id = id;
	
	this->shape.setSize(sf::Vector2f(width, height));
	this->shape.setPosition(sf::Vector2f(x, y));
	this->shape.setFillColor(idle_color);

	if(outline_idle_color != sf::Color::Transparent)
		this->shape.setOutlineThickness(1.f);
	this->shape.setOutlineColor(outline_idle_color);

	this->font = font;
	this->text.setFont(*this->font);
	this->text.setString(text);
	this->text.setFillColor(sf::Color::White);
	this->text.setCharacterSize(character_size);
	float text_x = this->shape.getPosition().x + (this->shape.getGlobalBounds().width - this->text.getGlobalBounds().width) / 2.f;
	float text_y = this->shape.getPosition().y + (this->shape.getGlobalBounds().height - this->text.getGlobalBounds().height) / 2.f;
	this->text.setPosition(text_x, text_y);

	this->textIdleColor = text_idle_color;
	this->textHoverColor = text_hover_color;
	this->textActiveColor = text_active_color;

	this->idleColor = idle_color;
	this->hoverColor = hover_color;
	this->activeColor = active_color;

	this->outlineActiveColor = outline_active_color;
	this->outlineHoverColor = outlineHoverColor;
	this->outlineIdleColor = outline_idle_color;
}

Button::~Button()
{
}

//Accessors
const bool Button::isPressed() const
{
	if (this->buttonState == BTN_ACTIVE)
	{
		return true;
	}
	return false;
}

const std::string Gui::Button::getText() const
{
	return this->text.getString();
}

const short unsigned& Gui::Button::getId() const
{
	return this->id;
}

//Modifier

void Gui::Button::setText(const std::string text)
{
	this->text.setString(text);
}

void Gui::Button::setId(const short unsigned id)
{
	this->id = id;
}

//Functions

void Button::update(const sf::Vector2f& mousePos)
{
	/*Update the booleans for hover and pressed*/

	//Idle
	this->buttonState = BTN_IDLE;

	//Hover
	if (this->shape.getGlobalBounds().contains(mousePos))
	{
		this->buttonState = BTN_HOVER;

		//Pressed
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
		{
			this->buttonState = BTN_ACTIVE;
		}
	}

	switch (this->buttonState)
	{
		case BTN_IDLE:
			this->shape.setFillColor(this->idleColor);
			this->text.setFillColor(this->textIdleColor);
			this->shape.setOutlineColor(this->outlineIdleColor);
			break;
		case BTN_HOVER: 
			this->shape.setFillColor(this->hoverColor);
			this->text.setFillColor(this->textHoverColor);
			this->shape.setOutlineColor(this->outlineHoverColor);
			break;
		case BTN_ACTIVE: 
			this->shape.setFillColor(this->activeColor);
			this->text.setFillColor(this->textActiveColor);
			this->shape.setOutlineColor(this->outlineActiveColor);
			break;
		default:
			this->shape.setFillColor(sf::Color::Red);
			this->text.setFillColor(sf::Color::White);
			this->shape.setOutlineColor(sf::Color::Transparent);
			break;
	}
}

void Button::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
	target.draw(this->text);
}
