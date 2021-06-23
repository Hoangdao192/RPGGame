#ifndef ANIMATION_H
#define ANIMATION_H

class Animation
{
public:
	//Variables
	sf::Sprite& sprite;
	sf::Texture& textureSheet;
	float animationTimer;
	float speed;
	float timer;
	bool done;
	int width;
	int height;

	sf::IntRect startRect;
	sf::IntRect currentRect;
	sf::IntRect endRect;

	Animation(sf::Sprite& sprite, sf::Texture& texture_sheet,
		float animation_timer,
		int start_frame_x, int start_frame_y,
		int frames_x, int frames_y, int width, int height);

	//Accessors
	const bool& isDone() const;

	//Functions
	const bool& play(const float& dt);
	const bool& play(const float& dt, float mod_percent);
	void pause();
	void reset();
};

#endif // ANIMATION_H

