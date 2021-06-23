#include "PreCompile.h"
#include "Animation.h"

Animation::Animation
(sf::Sprite& sprite, sf::Texture& texture_sheet,
	float animation_timer,
	int start_frame_x, int start_frame_y,
	int frames_x, int frames_y, int width, int height)
	:textureSheet(texture_sheet), sprite(sprite)
{
	this->done = false;
	this->timer = 0.f;
	this->animationTimer = animation_timer;
	this->speed = speed;
	this->width = width;
	this->height = height;
	this->startRect = sf::IntRect(start_frame_x * width, start_frame_y * height	, width, height);
	this->currentRect = this->startRect;
	this->endRect = sf::IntRect(frames_x * width, frames_y * height, width, height);

	this->sprite.setTexture(this->textureSheet, true);
	this->sprite.setTextureRect(this->startRect);
}


//Accessors
const bool& Animation::isDone() const
{
	return this->done;
}

//Functions

const bool& Animation::play(const float& dt)
{
	//Update timer
	this->done = false;
	this->timer += 100.f * dt;
	if (this->timer >= this->animationTimer)
	{
		//Reset timer
		this->timer = 0.f;

		//Animate
		if (this->currentRect != this->endRect)
		{
			this->currentRect.left += this->width;
		}
		else	//Reset
		{
			this->currentRect.left = this->startRect.left;
			this->done = true;
		}
	}
	this->sprite.setTextureRect(this->currentRect);
	return this->done;
}

const bool& Animation::play(const float& dt, float mod_percent)
{
	//Update timer
	if (mod_percent < 0.5f)
	{
		mod_percent = 0.5f;
	}

	this->done = false;	

	this->timer += mod_percent * 100.f * dt;
	if (this->timer >= this->animationTimer)
	{
		//Reset timer
		this->timer = 0.f;

		//Animate
		if (this->currentRect != this->endRect)
		{
			this->currentRect.left += this->width;
		}
		else	//Reset
		{
			this->currentRect.left = this->startRect.left;
			this->done = true;
		}

		this->sprite.setTextureRect(this->currentRect);
	}
	return this->done;
}

void Animation::pause()
{
}

void Animation::reset()
{
	this->timer = 0.f;
	this->currentRect = this->startRect;
}

