#include "PreCompile.h"
#include "TileMap.h"
#include <iomanip>

//Constructor/Destructor

TileMap::TileMap(float gridSize, unsigned width, unsigned height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeU = (unsigned) this->gridSizeF;
	this->maxSize.x = width;
	this->maxSize.y = height;
	this->layers = 1;
	this->textureFile = texture_file;

	//this->map.resize(this->maxSize.x);
	/*for (size_t x = 0; x < this->maxSize.x; ++x)
	{
		this->map.push_back(std::vector<std::vector<Tile*>>());
		for (size_t y = 0; y < this->maxSize.y; ++y)
		{
			this->map[x].push_back(std::vector<Tile*>());
			for (size_t z = 0; z < this->layers; ++z)
			{
				this->map[x][y].push_back(nullptr);
			}
		}
	}*/

	this->map.resize(this->maxSize.x);
	for (size_t x = 0; x < this->maxSize.x; ++x)
	{
		this->map[x].resize(this->maxSize.y);
		for (size_t y = 0; y < this->maxSize.y; ++y)
		{
			this->map[x][y].resize(this->layers, nullptr);
		}
	}

	if (!this->tileSheet.loadFromFile(texture_file))
	{
		std::cout << "\nERROR::TILEMAP::Failed to load " << texture_file;
	}
}

TileMap::~TileMap()
{
	this->clear();
}

//Accesssors

const sf::Texture* TileMap::getTileSheet() const
{
	return &this->tileSheet;
}

//Funtcions

void TileMap::update()
{
}

void TileMap::render(sf::RenderTarget& target)
{
	for (auto& x : this->map)
	{
		for (auto& y : x)
		{
			for (auto& z : y)
			{
				if (z != nullptr) { z->render(target); }
			}
		}
	}
}

void TileMap::addTile(const unsigned x, const unsigned y, const unsigned z, 
	const sf::IntRect& texture_rect,
	const bool collision, const short type)
{
	/*Take two indicies from the mouse position in the grid and add a tile to that position
	if the internal tilemap array allows it.*/
	if (x < this->maxSize.x && x >= 0 
		&& y >= 0 && y < this->maxSize.y
		&& z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == nullptr)
		{
			/*OK to add tile.*/
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type);
		}
	}
}

void TileMap::removeTile(const unsigned x, const unsigned y, const unsigned z)
{
	if (x < this->maxSize.x && x >= 0
		&& y >= 0 && y < this->maxSize.y
		&& z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] != nullptr)
		{
			delete this->map[x][y][z];
			this->map[x][y][z] = nullptr;
		}
	}
}

void TileMap::clear()
{
	for (size_t x = 0; x < this->maxSize.x; ++x)
	{
		for (size_t y = 0; y < this->maxSize.y; ++y)
		{
			for (size_t z = 0; z < this->layers; ++z)
			{
				if (this->map[x][y][z] != nullptr)
				{
					delete this->map[x][y][z];
					this->map[x][y][z] = nullptr;
				}
			}
		}
	}
}

void TileMap::saveToFile(const std::string file_name)
{
	/*Saves the entire tilemap to a text file
	Format:
	- Basic - 
	Size x y layers
	gridSize
	texture file path

	- All tiles - 
	gridPos x y layer, textureRect x y
	*/

	std::fstream file(file_name, std::ios::out);

	//SAVING
	//BASIC
	file << this->maxSize.x << " " <<	this->maxSize.y << " " << this->layers << "\n";
	file << this->gridSizeU << "\n";
	file << this->textureFile << "\n";

	//TILES
	for (size_t x = 0; x < this->maxSize.x; ++x)
	{
		for (size_t y = 0; y < this->maxSize.y; ++y)
		{
			for (size_t z = 0; z < this->layers; ++z)
			{
				if (this->map[x][y][z] != nullptr)
				{
					file << x << " " << y << " " << z << " " << this->map[x][y][z]->getAsString() << " ";
				}
			}
		}
	}

	file.close();
}

void TileMap::loadFromFile(const std::string file_name)
{
	this->clear();

	std::fstream file(file_name, std::ios::in);

	if (!file.is_open())
	{
		std::cout << "ERROR::CANNOT LOAD FILE " << file_name << std::endl;
		throw "ERROR::CANNOT LOAD FILE" + file_name;
	}

	sf::Vector2u size;
	unsigned gridSize = 0;
	unsigned layers = 0;
	std::string texture_path;

	//BASIC
	file >> size.x >> size.y >> layers >> gridSize >> texture_path;
	this->gridSizeU = gridSize;
	this->gridSizeF = gridSize;
	this->maxSize.x = size.x;
	this->maxSize.y = size.y;
	this->layers = layers;
	this->textureFile = texture_path;

	this->map.resize(this->maxSize.x);
	for (size_t x = 0; x < this->maxSize.x; ++x)
	{
		this->map[x].resize(this->maxSize.y);
		for (size_t y = 0; y < this->maxSize.y; ++y)
		{
			this->map[x][y].resize(this->layers, nullptr);
		}
	}

	//TILES
	unsigned x = 0;
	unsigned y = 0;
	unsigned z = 0;
	unsigned trX = 0;
	unsigned trY = 0;
	bool collision = false;
	short type = 0;

	while (file >> x >> y >> z >> trX >> trY >> collision >> type)
	{
		this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, sf::IntRect(trX, trY, gridSize, gridSize), collision, type);
	}

	file.close();
}
