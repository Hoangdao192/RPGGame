#include "PreCompile.h"
#include "Entity.h"

//Intializer

void Entity::initVariables()
{
	this->movementComponent = NULL;
	this->animationComponent = NULL;
	this->hitbboxComponent = NULL;
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
	if (this->hitbboxComponent)
	{
		delete this->hitbboxComponent;
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
	this->hitbboxComponent = new HitboxComponent(sprite, offset_x, offset_y, width, height);
}

void Entity::createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration)
{
	this->movementComponent = new MovementComponent(this->sprite,maxVelocity, acceleration, deceleration);
}

void Entity::createAnimationComponent(sf::Texture& texture_sheet)
{
	this->animationComponent = new AnimationComponent(this->sprite, texture_sheet);
}

//Functions

void Entity::setPosition(const float x, const float y)
{
	this->sprite.setPosition(x, y);
}

void Entity::move(const float dir_x, const float dir_y, const float& delta_time)
{
	if (this->movementComponent)
	{
		//Set velocity
		this->movementComponent->move(dir_x, dir_y, delta_time);
	}
}

void Entity::update(const float& delta_time)
{
}

void Entity::render(sf::RenderTarget& target)
{
	target.draw(this->sprite);

	if (this->hitbboxComponent)
	{
		this->hitbboxComponent->render(target);
	}

	std::cout << this->sprite.getOrigin().x << " " << this->sprite.getOrigin().y << "\n";
}
