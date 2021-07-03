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
	float x, y;
	sf::RectangleShape shape;
	bool collision;
	short type;
public:
	Tile(unsigned grid_x, unsigned grid_y, float gridSizeF, sf::Texture& texture,
		const sf::IntRect& texture_rect, bool collision = false, short type = TileType::DEFAULT);
	virtual ~Tile();

	const std::string getAsString() const;
	sf::Vector2f getPosition() { return sf::Vector2f(x, y); }

	//Functions
	void update();
	void render(sf::RenderTarget& target);
};

#endif // !TILE_H

