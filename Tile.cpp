#include "PreCompile.h"
#include "Tile.h"

Tile::Tile(int grid_x, int grid_y, float gridSizeF, sf::Texture& texture,
	const sf::IntRect& texture_rect, bool collision, short type)
{
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	//this->shape.setOutlineThickness(1);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(grid_x * gridSizeF, grid_y * gridSizeF);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);

	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{
}

//Accessors

const bool Tile::getCollision() const
{
	return this->collision;
}

const std::string Tile::getAsString() const
{
	std::stringstream ss;
	
	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top 
		<< " " << this->collision << " " << this->type;

	return ss.str();
}

const sf::Vector2f Tile::getPosition() const
{
	return this->shape.getPosition();
}

//Functions

const bool Tile::intersects(const sf::FloatRect bounds) const
{
	return this->shape.getGlobalBounds().intersects(bounds);
}

const sf::FloatRect Tile::getGlobalBounds() const
{
	return this->shape.getGlobalBounds();
}

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
