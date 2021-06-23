#include "PreCompile.h"
#include "Player.h"

//Initializer

void Player::initVariables()
{
	this->attacking = false;
}

void Player::initComponents()
{
	this->createMovementComponent(350.f, 15.f, 5.f);
	this->createHitboxComponent(this->sprite, 86.f, 74.f, 86.f, 120.f);
}

//Constructor/Destructor

Player::Player(float x, float y, sf::Texture& texture_sheet)
{
	this->initVariables();

	this->setPosition(x, y);

	this->initComponents();

	this->createAnimationComponent(texture_sheet);
	this->animationComponent->addAnimation("IDLE", 11.f, 0, 0, 13, 0, 192, 192);
	this->animationComponent->addAnimation("WALK", 7.f, 0, 1, 11, 1, 192, 192);
	this->animationComponent->addAnimation("ATTACK", 6.f, 0, 2, 13, 2, 384, 192);
}

Player::~Player()
{
}

//Functions

void Player::updateAttack()
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
	{
		this->attacking = true;
	}
}

void Player::updateAnimation(const float& dt)
{
	
	if (this->attacking)
	{
		//Sleep(1000);
		//Set origin depending on facing on direction
		if (this->sprite.getScale().x > 0.f)	//Facing left
		{
			this->sprite.setOrigin(96.f, 0.f);
		}
		else //Facing right
		{
			this->sprite.setOrigin(354.f, 0.f);
		}

		//Animate and check for animation end
		if (this->animationComponent->play("ATTACK", dt, true))
		{
			this->attacking = false;
			if (this->sprite.getScale().x > 0.f)	//Facing left
			{
				this->sprite.setOrigin(0.f, 0.f);
			}
			else if (this->sprite.getScale().x < 0.f)	//Facing right
			{
				this->sprite.setOrigin(258.f, 0.f);
			}
		}
	}
	//else
	if (this->movementComponent->getState(IDLE))
	{
		this->animationComponent->play("IDLE", dt);
	}
	else if (this->movementComponent->getState(MOVING_LEFT))
	{
		if (this->sprite.getScale().x < 0.f)
		{
			this->sprite.setOrigin(0.f, 0.f);
			this->sprite.setScale(1.f, 1.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_RIGHT))
	{
		if (this->sprite.getScale().x > 0.f)
		{
			this->sprite.setOrigin(258.f, 0.f);
			this->sprite.setScale(-1.f, 1.f);
		}
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().x, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_UP))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
	else if (this->movementComponent->getState(MOVING_DOWN))
	{
		this->animationComponent->play("WALK", dt, this->movementComponent->getVelocity().y, this->movementComponent->getMaxVelocity());
	}
}

void Player::update(const float& dt)
{
	this->movementComponent->update(dt);
	this->updateAnimation(dt);
	this->updateAttack();
	std::cout << animationComponent->getPlay() << "\n";
	this->hitbboxComponent->update();
}
