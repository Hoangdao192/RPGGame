#include "PreCompile.h"
#include "AnimationComponent.h"

//Initializer

//Constructor/Destructor

AnimationComponent::AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet)
	:sprite(sprite), textureSheet(texture_sheet)
{
	this->lastAnimation = NULL;
	this->priorityAnimation = NULL;
}

AnimationComponent::~AnimationComponent()
{
	std::map<std::string, Animation*>::iterator it = animations.begin();
	for (; it != animations.end(); ++it)
	{
		delete it->second;
	}
}

//Accessors
const bool& AnimationComponent::isDone(const std::string key)
{
	return this->animations[key]->isDone();
}

//Functions

void AnimationComponent::addAnimation
(	const std::string key,
	float animation_timer,
	int start_frame_x, int start_frame_y,
	int frames_x, int frames_y, int width, int height)
{
	playing = "none";
	this->animations[key] = new Animation(this->sprite, this->textureSheet,
		animation_timer, start_frame_x, start_frame_y,
		frames_x, frames_y, width, height);
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const bool priority)
{
	playing = key;
	if (priority)
	{
		this->priorityAnimation = this->animations[key];
	}
	if (this->priorityAnimation)	//If there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If he priority animation is done, remove it
			if (this->animations[key]->play(dt))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt);
	}

	return this->animations[key]->isDone();
}

const bool& AnimationComponent::play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority)
{
	playing = key;
	if (this->priorityAnimation)	//If there is a priority animation
	{
		if (this->priorityAnimation == this->animations[key])
		{
			if (this->lastAnimation != this->animations[key])
			{
				if (this->lastAnimation == NULL)
				{
					this->lastAnimation = this->animations[key];
				}
				else
				{
					this->lastAnimation->reset();
					this->lastAnimation = this->animations[key];
				}
			}

			//If he priority animation is done, remove it
			if (this->animations[key]->play(dt, abs(modifier / modifier_max)))
			{
				this->priorityAnimation = NULL;
			}
		}
	}
	else //Play animation of no other priority animation is set
	{
		//If this is a priority animation, set it.
		if (priority)
		{
			this->priorityAnimation = this->animations[key];
		}

		if (this->lastAnimation != this->animations[key])
		{
			if (this->lastAnimation == NULL)
			{
				this->lastAnimation = this->animations[key];
			}
			else
			{
				this->lastAnimation->reset();
				this->lastAnimation = this->animations[key];
			}
		}

		this->animations[key]->play(dt, abs(modifier / modifier_max));
	}
	return this->animations[key]->isDone();
}

