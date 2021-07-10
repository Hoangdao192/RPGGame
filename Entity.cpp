#include "PreCompile.h"
#include "Entity.h"

//Intializer

void Entity::initVariables()
{
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->hitboxComponent = NULL;
}

//Constructor/Destructor

Entity::Entity()
{
	this->initVariables();
}

Entity::~Entity()
{
	//Do not delete texture because it is loaded from out side
	if (movementComponent)
	{ 
		delete this->movementComponent;
	}	
	if (this->animationComponent)
	{
		delete this->animationComponent;
	}
	if (this->hitboxComponent)
	{
		delete this->hitboxComponent;
	}
	if (this->attributeComponent)
	{
		delete this->attributeComponent;
	}
}

//Component functions

void Entity::setTexture(sf::Texture& texture)
{
	this->sprite.setTexture(texture);
}

void Entity::createHitboxComponent(sf::Sprite& sprite,
	float offset_x, float offset_y,
	float width, float height)
{
	this->hitboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite,maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

void Entity::createAttributeComponent(const int level)
{
	this->attributeComponent = new AttributeCompponent(level);
}

const sf::Vector2f Entity::getPosition() const
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getPosition();
	}
	return this->sprite.getPosition();
}

const sf::Vector2i Entity::getGridPosition(const unsigned gridSizeU) const
{
	if (this->hitboxComponent)
	{
		return sf::Vector2i(
			(int)this->hitboxComponent->getPosition().x / gridSizeU,
			(int)this->hitboxComponent->getPosition().y / gridSizeU);
	}
	else
	{
		return sf::Vector2i(
			(int)this->sprite.getPosition().x / gridSizeU,
			(int)this->sprite.getPosition().y / gridSizeU);
	}
}

const sf::FloatRect Entity::getGlobalBounds() const
{
	if (this->hitboxComponent)
	{
		return this->hitboxComponent->getGlobalBounds();
	}
	return this->sprite.getGlobalBounds();
}

const sf::FloatRect Entity::getNextPositionBounds(const float& dt) const
{
	if (this->hitboxComponent && this->movementComponent)
	{
		return this->hitboxComponent->getNextPosition(this->movementComponent->getVelocity() * dt);
	}

	return sf::FloatRect(-1.f, -1.f, -1.f, -1.f);
}

//Functions

void Entity::setPosition(const float x, const float y)
{
	if (this->hitboxComponent) { this->hitboxComponent->setPosition(sf::Vector2f(x, y)); }
	else { this->sprite.setPosition(x, y); }
}

void Entity::move(const float dir_x, const float dir_y, const float& delta_time)
{
	if (this->movementComponent) { this->movementComponent->move(dir_x, dir_y, delta_time); }
}

void Entity::stopVelocity()
{
	if (this->movementComponent) { this->movementComponent->stopVelocity(); }
}

void Entity::stopVelocityX()
{
	if (this->movementComponent) { this->movementComponent->stopVelocityX(); }
}

void Entity::stopVelocityY()
{
	if (this->movementComponent) { this->movementComponent->stopVelocityY(); }
}

void Entity::update(const float& delta_time)
{
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitboxComponent)
	{
		this->hitboxComponent->render(target);
	}
}
