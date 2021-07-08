#ifndef TILE_H
#define TILE_H

enum TileType
{
	DEFAULT = 0,
	DAMAGING
};

class Tile
{
private:

protected:
	sf::RectangleShape shape;
	bool collision;
	short type;
public:
	Tile(int grid_x, int grid_y, float gridSizeF, sf::Texture& texture,
		const sf::IntRect& texture_rect, bool collision = false, short type = TileType::DEFAULT);
	virtual ~Tile();

	//Accessors
	const bool getCollision() const;
	const bool intersects(const sf::FloatRect bounds) const;
	const sf::FloatRect getGlobalBounds() const;
	const std::string getAsString() const;
	const sf::Vector2f getPosition() const;

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

#endif // !TILE_H

