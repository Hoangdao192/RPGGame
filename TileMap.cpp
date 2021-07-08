#include "PreCompile.h"
#include "TileMap.h"
#include <iomanip>

//Constructor/Destructor

TileMap::TileMap(float gridSize, int width, int height, std::string texture_file)
{
	this->gridSizeF = gridSize;
	this->gridSizeI = (int) this->gridSizeF;
	this->maxSizeGrid.x = width;
	this->maxSizeGrid.y = height;
	this->maxSizeWorld.x = width * this->gridSizeF;
	this->maxSizeWorld.y = height * this->gridSizeF;

	this->layers = 1;
	this->textureFile = texture_file;

	this->fromX = 0;
	this->toX = 0;
	this->fromY = 0;
	this->toY = 0;
	this->layer = 0;

	this->map.resize(this->maxSizeGrid.x);
	for (int x = 0; x < this->maxSizeGrid.x; ++x)
	{
		this->map[x].resize(this->maxSizeGrid.y);
		for (int y = 0; y < this->maxSizeGrid.y; ++y)
		{
			this->map[x][y].resize(this->layers, nullptr);
		}
	}

	if (!this->tileSheet.loadFromFile(texture_file))
	{
		std::cout << "\nERROR::TILEMAP::Failed to load " << texture_file << std::endl;
	}

	this->collisionBox.setSize(sf::Vector2f(gridSize, gridSize));
	this->collisionBox.setFillColor(sf::Color(255, 0, 0, 50));
	this->collisionBox.setOutlineThickness(1);
	this->collisionBox.setOutlineColor(sf::Color::Red);
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

void TileMap::render(sf::RenderTarget& target, Entity* entity)
{
	if (entity)
	{
		this->layer = 0;
		this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
		if (this->fromX < 0) { this->fromX = 0; }
		else if (this->fromX > this->maxSizeGrid.x) { this->fromX = this->maxSizeGrid.x; }

		this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
		if (this->toX < 0) { this->toX = 0; }
		else if (this->toX > this->maxSizeGrid.x) { this->toX = this->maxSizeGrid.x; }

		this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
		if (this->fromY < 0) { this->fromY = 0; }
		else if (this->fromY > this->maxSizeGrid.y) { this->fromY = this->maxSizeGrid.y; }

		this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
		if (this->toY < 0) { this->toY = 0; }
		else if (this->toY > this->maxSizeGrid.y) { this->toY = this->maxSizeGrid.y; }

		for (int x = this->fromX; x < this->toX; ++x)
		{
			for (int y = this->fromY; y < this->toY; ++y)
			{
				if (this->map[x][y][this->layer] != nullptr)
				{
					this->map[x][y][this->layer]->render(target);
					if (this->map[x][y][this->layer]->getCollision())
					{
						this->collisionBox.setPosition(this->map[x][y][this->layer]->getPosition());
						target.draw(this->collisionBox);
					}
				}
			}
		}
	}
	else
	{
		target.draw(this->collisionBox);
		for (auto& x : this->map)
		{
			for (auto& y : x)
			{
				for (auto& z : y)
				{
					if (z != nullptr)
					{
						z->render(target);
						if (z->getCollision())
						{
							this->collisionBox.setPosition(z->getPosition());
							target.draw(this->collisionBox);
						}
					}
				}
			}
		}
	}
}

void TileMap::addTile(const int x, const int y, const int z,
	const sf::IntRect& texture_rect,
	const bool collision, const short type)
{
	/*Take two indicies from the mouse position in the grid and add a tile to that position
	if the internal tilemap array allows it.*/
	if (x < this->maxSizeGrid.x && x >= 0 
		&& y >= 0 && y < this->maxSizeGrid.y
		&& z < this->layers && z >= 0)
	{
		if (this->map[x][y][z] == nullptr)
		{
			/*OK to add tile.*/
			this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, texture_rect, collision, type);
		}
	}
}

void TileMap::removeTile(const int x, const int y, const int z)
{
	if (x < this->maxSizeGrid.x && x >= 0
		&& y >= 0 && y < this->maxSizeGrid.y
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
	for (int x = 0; x < this->maxSizeGrid.x; ++x)
	{
		for (int y = 0; y < this->maxSizeGrid.y; ++y)
		{
			for (int z = 0; z < this->layers; ++z)
			{
				if (this->map[x][y][z] != nullptr)
				{
					delete this->map[x][y][z];
					this->map[x][y][z] = nullptr;
				}
			}
			this->map[x][y].clear();
		}
		this->map[x].clear();
	}
	this->map.clear();
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
	file << this->maxSizeGrid.x << " " <<	this->maxSizeGrid.y << " " << this->layers << "\n";
	file << this->gridSizeI << "\n";
	file << this->textureFile << "\n";

	//TILES
	for (int x = 0; x < this->maxSizeGrid.x; ++x)
	{
		for (int y = 0; y < this->maxSizeGrid.y; ++y)
		{
			for (int z = 0; z < this->layers; ++z)
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

	sf::Vector2i size;
	int gridSize = 0;
	int layers = 0;
	std::string texture_path;

	//BASIC
	file >> size.x >> size.y >> layers >> gridSize >> texture_path;
	this->gridSizeI = gridSize;
	this->gridSizeF = (float) gridSize;
	this->maxSizeGrid.x = size.x;
	this->maxSizeGrid.y = size.y;
	this->layers = layers;
	this->textureFile = texture_path;

	this->map.resize(this->maxSizeGrid.x);
	for (int x = 0; x < this->maxSizeGrid.x; ++x)
	{
		this->map[x].resize(this->maxSizeGrid.y);
		for (int y = 0; y < this->maxSizeGrid.y; ++y)
		{
			this->map[x][y].resize(this->layers, nullptr);
		}
	}

	//TILES
	int x = 0;
	int y = 0;
	int z = 0;
	int trX = 0;
	int trY = 0;
	bool collision = false;
	short type = 0;

	while (file >> x >> y >> z >> trX >> trY >> collision >> type)
	{
		this->map[x][y][z] = new Tile(x, y, this->gridSizeF, this->tileSheet, sf::IntRect(trX, trY, gridSize, gridSize), collision, type);
	}

	file.close();
}

void TileMap::updateCollision(Entity* entity, const float& dt)
{
	//WORLD BOUNDS
	if (entity->getPosition().x < 0.f)
	{
		entity->setPosition(0.f, entity->getPosition().y);
		entity->stopVelocityX();
	}
	else if (entity->getPosition().x + entity->getGlobalBounds().width > (float)this->maxSizeGrid.x * this->gridSizeF)
	{
		entity->setPosition((float)this->maxSizeGrid.x * this->gridSizeF - entity->getGlobalBounds().width, entity->getPosition().y);
		entity->stopVelocityX();
	}

	if (entity->getPosition().y < 0.f) 
	{ 
		entity->setPosition(entity->getPosition().x, 0.f); 
		entity->stopVelocityY();
	}
	else if (entity->getPosition().y + entity->getGlobalBounds().height > (float)this->maxSizeGrid.y * this->gridSizeF)
	{
		entity->setPosition(entity->getPosition().x, (float)this->maxSizeGrid.y * this->gridSizeF - entity->getGlobalBounds().height);
		entity->stopVelocityY();
	}

	//TILES
	this->layer = 0;
	this->fromX = entity->getGridPosition(this->gridSizeI).x - 1;
	if (this->fromX < 0) { this->fromX = 0; }
	else if (this->fromX > this->maxSizeGrid.x) { this->fromX = this->maxSizeGrid.x; }

	this->toX = entity->getGridPosition(this->gridSizeI).x + 3;
	if (this->toX < 0) { this->toX = 0; }
	else if (this->toX > this->maxSizeGrid.x) { this->toX = this->maxSizeGrid.x; }

	this->fromY = entity->getGridPosition(this->gridSizeI).y - 1;
	if (this->fromY < 0) { this->fromY = 0; }
	else if (this->fromY > this->maxSizeGrid.y) { this->fromY = this->maxSizeGrid.y; }

	this->toY = entity->getGridPosition(this->gridSizeI).y + 3;
	if (this->toY < 0) { this->toY = 0; }
	else if (this->toY > this->maxSizeGrid.y) { this->toY = this->maxSizeGrid.y; }

	for (int x = this->fromX; x < this->toX; ++x)
	{
		for (int y = this->fromY; y < this->toY; ++y)
		{
			if (this->map[x][y][this->layer] == nullptr) { continue; }

			sf::FloatRect wallBounds = this->map[x][y][this->layer]->getGlobalBounds();
			sf::FloatRect playerBounds = entity->getGlobalBounds();
			sf::FloatRect nextPositionBounds = entity->getNextPositionBounds(dt);

			if (this->map[x][y][this->layer]->getCollision() 
				&& this->map[x][y][this->layer]->intersects(nextPositionBounds/*entity->getGlobalBounds()*/))
			{
				//Bottom collision
				if (playerBounds.top < wallBounds.top
					&& playerBounds.top + playerBounds.height < wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left)
				{
					entity->stopVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top - playerBounds.height);
				}

				//Top collision
				else if (playerBounds.top > wallBounds.top
					&& playerBounds.top + playerBounds.height > wallBounds.top + wallBounds.height
					&& playerBounds.left < wallBounds.left + wallBounds.width
					&& playerBounds.left + playerBounds.width > wallBounds.left)
				{
					entity->stopVelocityY();
					entity->setPosition(playerBounds.left, wallBounds.top + wallBounds.height);
				}
				//Left collision
				else if (playerBounds.left > wallBounds.left
					&& playerBounds.left + playerBounds.width > wallBounds.left + wallBounds.width
					&& playerBounds.top < wallBounds.top + wallBounds.height
					&& playerBounds.top + playerBounds.height > wallBounds.top)
				{
					entity->stopVelocityX();
					entity->setPosition(wallBounds.left + wallBounds.width, playerBounds.top);
				}
				//Right collision
				else if (playerBounds.left < wallBounds.left
					&& playerBounds.left + playerBounds.width < wallBounds.left + wallBounds.width
					&& playerBounds.top < wallBounds.top + wallBounds.height
					&& playerBounds.top + playerBounds.height > wallBounds.top)
				{
					entity->stopVelocityX();
					entity->setPosition(wallBounds.left - playerBounds.width, playerBounds.top);
				}

			}
		}	
	}
}
