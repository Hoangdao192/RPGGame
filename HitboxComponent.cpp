#include "PreCompile.h"
#include "HitboxComponent.h"

//Contructor/Destructor

HitboxComponent::HitboxComponent(sf::Sprite& sprite, 
	float offset_x, float offset_y, 
	float width, float height)
	:sprite(sprite)
{
	this->hitbox.setPosition(this->sprite.getPosition().x + offset_x, this->sprite.getPosition().y + offset_y);
	this->hitbox.setSize(sf::Vector2f(width, height));
	this->hitbox.setFillColor(sf::Color::Transparent);
	this->hitbox.setOutlineThickness(1.f);
	this->hitbox.setOutlineColor(sf::Color::Green);
	this->offsetX = offset_x;
	this->offsetY = offset_y;
}

HitboxComponent::~HitboxComponent()
{
}

//Functions

bool HitboxComponent::checkIntersect(const sf::FloatRect& frect)
{
	return this->hitbox.getGlobalBounds().intersects(frect);
}

void HitboxComponent::update()
{
	this->hitbox.setPosition(this->sprite.getPosition().x + this->offsetX, this->sprite.getPosition().y + this->offsetY);
}

void HitboxComponent::render(sf::RenderTarget& target)
{
	target.draw(this->hitbox);
}
