#include "PreCompile.h"
#include "GameState.h"

//Initializer

void GameState::initKeybinds()
{
	std::fstream file("Config/gamestate_keybinds.ini", std::ios::in);
	if (!file.is_open())
	{
		std::cout << "\nError: Cannot load file Config/gamestate_keybinds.ini";
	}

	while (!file.eof())
	{
		std::string keybind, keybind_value;
		file >> keybind >> keybind_value;
		this->keybinds[keybind] = this->supportedKeys->at(keybind_value);
	}

	file.close();
}

void GameState::initTextures()
{
	if (!this->textures["PLAYER_SHEET"].loadFromFile("Resources/Images/Sprites/Player/PLAYER_SHEET.png"))
	{
		std::cerr << "\nERROR: Cannot load file: Resources/Images/Sprites/Player/PLAYER_SHEET.png";
	}
}

void GameState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);
	this->pauseMenu->addButton("EXIT_STATE", 420, "Quit");
}

void GameState::initPlayers()
{
	this->player = new Player(0, 0, this->textures["PLAYER_SHEET"]);
}

void GameState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10, 10);
}

void GameState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Quicksand.ttf"))
	{
		throw("Error: MainMenuState->initFonts: could not load font Fonts/Quicksand.ttf");
	}

}


//Constructor/Destructor

GameState::GameState(StateData* state_data)
	:State(state_data)
{
	this->initFonts();
	this->initKeybinds();
	this->initTextures();
	this->initPauseMenu();
	this->initPlayers();
	this->initTileMap();
}

GameState::~GameState()
{
	delete this->player;
	delete this->pauseMenu;
	delete this->tileMap;
}

void GameState::updatePlayerInput(const float& delta_time)
{	

	//Update player input (convert int to enum sf::Keyboard::Key)
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keybinds.at("MOVE_LEFT")))
	{
		this->player->move(-1.f, 0.f, delta_time);
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keybinds.at("MOVE_RIGHT")))
	{
		this->player->move(1.f, 0.f, delta_time);
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keybinds.at("MOVE_UP")))
	{
		this->player->move(0.f, -1.f, delta_time);
	}
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keybinds.at("MOVE_DOWN")))
	{
		this->player->move(0.f, 1.f, delta_time);
	}
}

void GameState::updateInput(const float& dt)
{
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keybinds.at("CLOSE")) && this->getKeyTime())
	{
		if (!this->paused){	this->pauseState();	}
		else { this->unpauseState(); }
	}
}

void GameState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("EXIT_STATE"))
	{
		this->endState();
	}
}

void GameState::update(const float& delta_time)
{
	this->updateMousePosition();	
	this->updateKeyTime(delta_time);
	this->updateInput(delta_time);
	
	if (!this->paused)	//Unpaused update
	{
		this->updatePlayerInput(delta_time);
		this->player->update(delta_time);
	}
	else //Paused update
	{
		this->pauseMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}
}

void GameState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		std::cout << "\ntarget not set. set to default = window";
		target = this->window;
	}

	//this->tileMap.render(*target);

	this->player->render(*target);

	if (this->paused)	//Paused menu render
	{
		this->pauseMenu->render(*target);
	}
}
