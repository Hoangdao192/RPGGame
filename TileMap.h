#ifndef TILEMAP_H
#define TILEMAP_H

#include"Tile.h"
#include "Entity.h"

class TileMap
{
private:
	
	//Variables
	float gridSizeF;
	int gridSizeI;
	sf::Vector2i maxSizeGrid;
	sf::Vector2f maxSizeWorld;
	int layers;
	std::vector<std::vector<std::vector<std::vector<Tile*>>>> map;

	std::string textureFile;
	sf::Texture tileSheet;

	sf::RectangleShape collisionBox;

	//Culling
	int fromX;
	int toX;
	int fromY;
	int toY;
	int layer;

	//Functions
	void clear();

public:
	TileMap(float gridSize, int width, int height, std::string texture_file);
	virtual ~TileMap();

	//Accessors
	const sf::Texture* getTileSheet() const;

	//Functions
	void update();
	void render(sf::RenderTarget& target, Entity* entity = nullptr);

	void addTile(const int x, const int y, const int z,
		const sf::IntRect& texture_rect,
		const bool collision, const short type);
	void removeTile(const int x, const int y, const int z);

	void saveToFile(const std::string file_name);
	void loadFromFile(const std::string file_name);

	void updateCollision(Entity* entity, const float& dt);
};

#endif // !TILEMAP_H