#ifndef ANIMATIONCOMPONENT_H
#define ANIMATIONCOMPONENT_H

#include "Animation.h"

class AnimationComponent
{
private:

	//Variables
	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	std::map<std::string, Animation*> animations;
	Animation* lastAnimation;
	Animation* priorityAnimation;

	std::string playing;
	//Initializer

public:
	AnimationComponent(sf::Sprite& sprite, sf::Texture& texture_sheet);
	virtual ~AnimationComponent();

	//Accessors
	const bool& isDone(const std::string key);
	std::string getPlay() { return playing; }

	//Functions
	void addAnimation(const std::string key,
		float animation_timer,
		int start_frame_x, int start_frame_y,
		int frames_x, int frames_y, int width, int height);
	
	const bool& play(const std::string key, const float& dt, const bool priority = false);
	const bool& play(const std::string key, const float& dt, const float& modifier, const float& modifier_max, const bool priority = false);
};

#endif // !ANIMATIONCOMPONENT_H

