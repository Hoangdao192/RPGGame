#ifndef HITBOXCOMPONENT_H
#define HITBOXCOMPONENT_H

class HitboxComponent
{
private:
	//Variables
	sf::Sprite& sprite;
	sf::RectangleShape hitbox;
	sf::FloatRect nextPosition;
	float offsetX;
	float offsetY;

public:
	HitboxComponent(sf::Sprite& sprite,
		float offset_x, float offset_y, 
		float width, float height);
	virtual ~HitboxComponent();

	//Accessors
	const sf::Vector2f& getPosition() const;
	const sf::FloatRect getGlobalBounds() const;
	const sf::FloatRect& getNextPosition(const sf::Vector2f& velocity);

	//Functions
	bool intersects(const sf::FloatRect& frect);

	void setPosition(const sf::Vector2f position);

	void update();
	void render(sf::RenderTarget& target);
};

#endif // !HITBOXCOMPONENT_H

