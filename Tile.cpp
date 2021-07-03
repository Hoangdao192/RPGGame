#include "PreCompile.h"
#include "Tile.h"

Tile::Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, sf::Texture& texture, 
	const sf::IntRect& texture_rect, bool collision, short type)
{
	this->x = grid_x;
	this->y = grid_y;
	this->shape.setSize(sf::Vector2f(gridSizeF, gridSizeF));
	this->shape.setFillColor(sf::Color::White);
	//this->shape.setOutlineThickness(1);
	//this->shape.setOutlineColor(sf::Color::Black);
	this->shape.setPosition(x * gridSizeF, y * gridSizeF);
	this->shape.setTexture(&texture);
	this->shape.setTextureRect(texture_rect);

	this->collision = collision;
	this->type = type;
}

Tile::~Tile()
{
}

//Accessors

const std::string Tile::getAsString() const
{
	std::stringstream ss;
	
	ss << this->shape.getTextureRect().left << " " << this->shape.getTextureRect().top 
		<< " " << this->collision << " " << this->type;

	return ss.str();
}

//Functions

void Tile::update()
{
}

void Tile::render(sf::RenderTarget& target)
{
	target.draw(this->shape);
}
