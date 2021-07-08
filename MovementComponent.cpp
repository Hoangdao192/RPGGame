#include "PreCompile.h"
#include "MovementComponent.h"

//Initializer

//Constructor/Destructor

MovementComponent::MovementComponent(sf::Sprite& sprite,
	float maxVelocity, float acceleration, float deceleration)
	:sprite(sprite)
{
	this->acceleration = acceleration;
	this->deceleration = deceleration;
	this->maxVelocity = maxVelocity;
}

MovementComponent::~MovementComponent()
{
}

//Accessors

const sf::Vector2f MovementComponent::getVelocity() const
{
	return this->velocity;
}

const float& MovementComponent::getMaxVelocity() const
{
	return this->maxVelocity;
}

//Functions

const bool MovementComponent::getState(const short unsigned state)
{
	switch (state)
	{
		case IDLE: 
			if (this->velocity.x == 0.f && this->velocity.y == 0.f)
				return true;
			break;
		case MOVING:
			if (this->velocity.x != 0.f || this->velocity.y != 0.f)
				return true;
			break;
		case MOVING_LEFT: 
			if (this->velocity.x < 0.f)
				return true;
			break;
		case MOVING_RIGHT: 
			if (this->velocity.x > 0.f)
				return true;
			break;
		case MOVING_UP:
			if (this->velocity.y < 0.f)
				return true;
			break;
		case MOVING_DOWN:
			if (this->velocity.y > 0.f)
				return true;
			break;
	}
	return false;
}

void MovementComponent::stopVelocity()
{
	/*Reset the velocity to 0.*/
	this->stopVelocityX();
	this->stopVelocityY();	
}

void MovementComponent::stopVelocityX()
{
	this->velocity.x = 0;
}

void MovementComponent::stopVelocityY()
{
	this->velocity.y = 0;
}

void MovementComponent::move(const float dir_x, const float dir_y, const float& delta_time)
{
	/*Accelerating a sprite until it reaches the max velocity*/
	this->velocity.x += this->acceleration * dir_x;
	this->velocity.y += this->acceleration * dir_y;
}

void MovementComponent::update(const float& dt)
{
	/*
	Decelerate the sprite and controls the maximum velocity .
	Moves the sprite. 
	*/

	//X
	if (this->velocity.x > 0.f)	// Check for right
	{
		//Max velocity
		if (this->velocity.x > this->maxVelocity) { this->velocity.x = this->maxVelocity; }

		//Deceleration
		this->velocity.x -= deceleration;
		if (this->velocity.x < 0.f) { this->velocity.x = 0.f; }
	}
	else if (this->velocity.x < 0.f)	// Check for left
	{
		//Max velocity
		if (this->velocity.x < -this->maxVelocity) { this->velocity.x = -this->maxVelocity; }

		//Deceleration
		this->velocity.x += deceleration;
		if (this->velocity.x > 0.f) { this->velocity.x = 0.f; }
	}

	//Y
	if (this->velocity.y > 0.f)	// Check for down
	{
		//Max velocity
		if (this->velocity.y > this->maxVelocity) { this->velocity.y = this->maxVelocity; }

		//Deceleration
		this->velocity.y -= deceleration;
		if (this->velocity.y < 0.f) { this->velocity.y = 0.f; }
	}
	else if (this->velocity.y < 0.f)	// Check for up
	{
		//Max velocity
		if (this->velocity.y < -this->maxVelocity) { this->velocity.y = -this->maxVelocity; }

		//Deceleration
		this->velocity.y += deceleration;
		if (this->velocity.y > 0.f) { this->velocity.y = 0.f; }
	}

	//Final move
	this->sprite.move(this->velocity * dt);
}
