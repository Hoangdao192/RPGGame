#include "PreCompile.h"
#include "EditorState.h"

//Initializer

void EditorState::initVariables()
{
	this->textureRect = sf::IntRect(0, 0, (int)this->stateData->gridSize, (int)this->stateData->gridSize);
}

void EditorState::initBackground()
{
}

void EditorState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Quicksand.ttf"))
	{
		throw("Error: EditorState->initFonts: could not load font Fonts/Quicksand.ttf");
	}

}

void EditorState::initText()
{
	//REMOVE LATER
	this->cursorText.setCharacterSize(20);
	this->cursorText.setFillColor(sf::Color::White);
	this->cursorText.setFont(this->font);
}

void EditorState::initKeybinds()
{
	std::fstream file("Config/editorstate_keybinds.ini", std::ios::in);
	if (!file.is_open())
	{
		std::cout << "\nError: Cannot load file Config/editorstate_keybinds.ini";
	}

	while (!file.eof())
	{
		std::string keybind, keybind_value;
		file >> keybind >> keybind_value;
		this->keybinds[keybind] = this->supportedKeys->at(keybind_value);
	}

	file.close();
}

void EditorState::initButtons()
{
}

void EditorState::initGui()
{
	this->sidebar.setSize(sf::Vector2f(80, (float)this->stateData->gfxSettings->resolution.height));
	this->sidebar.setFillColor(sf::Color(50, 50, 50, 100));
	this->sidebar.setOutlineColor(sf::Color(200, 200, 200, 150));
	this->sidebar.setOutlineThickness(1);

	this->selectorRect.setTexture(this->tileMap->getTileSheet());
	this->selectorRect.setSize(sf::Vector2f(this->stateData->gridSize, this->stateData->gridSize));
	//this->selectorRect.setFillColor(sf::Color::Transparent);
	this->selectorRect.setOutlineThickness(1.f);
	this->selectorRect.setTextureRect(this->textureRect);
	this->selectorRect.setOutlineColor(sf::Color::Green);

	this->textureSelector = new TextureSelector(0, 0, 500, 500, this->stateData->gridSize, this->tileMap->getTileSheet(), this->font);
}

void EditorState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);
	this->pauseMenu->addButton("QUIT", 420, "Quit");
	this->pauseMenu->addButton("SAVE", 320, "Save");
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10,10, "Resources/Images/Tiles/tilesheet1.png");
	this->tileMap->loadFromFile("tilemap.txt");
}

//Constructor/Destructor

EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initText();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
	this->initGui();
}

EditorState::~EditorState()
{
	for (std::map<std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pauseMenu;

	delete this->tileMap;

	delete this->textureSelector;
}

//Functions

void EditorState::updateInput(const float& delta_time)
{
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key) this->keybinds["CLOSE"]) && this->getKeyTime())
	{
		if (!this->paused) { this->pauseState(); }
		else { this->unpauseState(); }
	}
}

void EditorState::updateEditorInput(const float& dt)
{
	//Add a tile to the tilemap
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && this->getKeyTime())
	{
		if (!this->sidebar.getGlobalBounds().contains((sf::Vector2f)this->mousePosWindow))
		{
			if (!this->textureSelector->getActive())
			{
				this->tileMap->addTile(this->mousePosGrid.x, this->mousePosGrid.y, 0, this->textureRect);
			}
			else
			{
				this->textureRect = this->textureSelector->getTextureRect();
			}
		}
	}
	else
	//	Remove a tile
	if(sf::Mouse::isButtonPressed(sf::Mouse::Right) && this->getKeyTime())
	{
		if (!this->textureSelector->getActive()
		&& !this->sidebar.getGlobalBounds().contains((sf::Vector2f)this->mousePosWindow))
		{
			this->tileMap->removeTile(this->mousePosGrid.x, this->mousePosGrid.y, 0);
		}
	}
}

void EditorState::updateButtons()
{
	/*Update all the buttons in the state and handles their functionality*/

	std::map<std::string, Button*>::iterator it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
	{
		it->second->update(this->mousePosView);
	}
}

void EditorState::updateGui(const float& dt)
{
	this->textureSelector->update(this->mousePosWindow, dt);

	if (!this->textureSelector->getActive())
	{
		this->selectorRect.setTextureRect(this->textureRect);
		this->selectorRect.setPosition((sf::Vector2f)this->mousePosGrid * this->gridSize);
	}

	std::stringstream ss;
	this->cursorText.setPosition(this->mousePosView.x+100, this->mousePosView.y);
	ss << this->mousePosView.x << ", " << this->mousePosView.y << "\n"
		<< this->mousePosGrid.x << " " << this->mousePosGrid.y << "\n"
		<< this->textureRect.left << " " << this->textureRect.top;
	this->cursorText.setString(ss.str());
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->endState();
	if (this->pauseMenu->isButtonPressed("SAVE")) { this->tileMap->saveToFile("tilemap.txt"); }
}

void EditorState::update(const float& delta_time)
{
	this->updateMousePosition();
	this->updateKeyTime(delta_time); 
	this->updateInput(delta_time);

	if (!this->paused)	//Unpaused
	{
		this->updateButtons();
		this->updateGui(delta_time);
		this->updateEditorInput(delta_time);
	}
	else  //Paused
	{
		this->pauseMenu->update(this->mousePosView);
		this->updatePauseMenuButtons();
	}

	this->updateButtons();
}

void EditorState::renderButtons(sf::RenderTarget& target)
{
	std::map<std::string, Button*>::iterator it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
	{
		it->second->render(target);
	}
}

void EditorState::renderGui(sf::RenderTarget& target)
{
	target.draw(this->selectorRect); 
	this->textureSelector->render(target); 
	target.draw(this->cursorText);

	target.draw(this->sidebar);
}

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		std::cout << "\ntarget not set. set to default = window";
		target = this->window;
	}

	if (this->paused)
	{
		this->pauseMenu->render(*target);
	}
	else
	{
		this->renderButtons(*target);
		this->tileMap->render(*target);
		this->renderGui(*target);
	}
}
