#ifndef ENTITY_H
#define ENTITY_H

#include "MovementComponent.h"
#include "AnimationComponent.h"
#include "HitboxComponent.h"
#include "AttributeCompponent.h"

class Entity
{
private:
	void initVariables();

protected:
	sf::Sprite sprite;

	HitboxComponent* hitboxComponent;
	MovementComponent* movementComponent;
	AnimationComponent* animationComponent;
	AttributeCompponent* attributeComponent;

public:
	Entity();
	virtual ~Entity();

	//Component functions
	void setTexture(sf::Texture& texture);
	void createHitboxComponent(sf::Sprite& sprite, 
		float offset_x, float offset_y,
		float width, float height);
	void createMovementComponent(const float maxVelocity, const float acceleration, const float deceleration);
	void createAnimationComponent(sf::Texture& texture_sheet);
	void createAttributeComponent(const int level);

	//Accessors
	virtual const sf::Vector2f getPosition() const;
	virtual const sf::Vector2i getGridPosition(const unsigned gridSizeU) const;
	virtual const sf::FloatRect getGlobalBounds() const;
	virtual const sf::FloatRect getNextPositionBounds(const float& dt) const;
	
	//Functions
	virtual void setPosition(const float x, const float y);
	virtual void move(const float dir_x, const float dir_y, const float& delta_time);
	virtual void stopVelocity();
	virtual void stopVelocityX();
	virtual void stopVelocityY();

	virtual void update(const float& delta_time) = 0;
	virtual void render(sf::RenderTarget& target) = 0;
};

#endif // ! ENTITY_H
