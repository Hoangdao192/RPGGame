#include "PreCompile.h"
#include "EditorState.h"

//Initializer

void EditorState::initVariables()
{
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

void EditorState::initPauseMenu()
{
	this->pauseMenu = new PauseMenu(*this->window, this->font);
	this->pauseMenu->addButton("QUIT", 420, "Quit");
}

void EditorState::initTileMap()
{
	this->tileMap = new TileMap(this->stateData->gridSize, 10,10);
}

//Constructor/Destructor

EditorState::EditorState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initPauseMenu();
	this->initButtons();
	this->initTileMap();
}

EditorState::~EditorState()
{
	for (std::map<std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}

	delete this->pauseMenu;

	delete this->tileMap;
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

void EditorState::updateButtons()
{
	/*Update all the buttons in the state and handles their functionality*/

	std::map<std::string, Button*>::iterator it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
	{
		it->second->update(this->mousePosView);
	}
}

void EditorState::updatePauseMenuButtons()
{
	if (this->pauseMenu->isButtonPressed("QUIT"))
		this->endState();
}

void EditorState::update(const float& delta_time)
{
	this->updateMousePosition();
	this->updateKeyTime(delta_time); 
	this->updateInput(delta_time);

	if (!this->paused)	//Unpaused
	{
		this->updateButtons();
	}
	else
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

void EditorState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		std::cout << "\ntarget not set. set to default = window";
		target = this->window;
	}


	this->renderButtons(*target);

	this->tileMap->render(*target);

	if (this->paused)
	{
		this->pauseMenu->render(*target);
	}

	//REMOVE LATER!!!
	sf::Text mouseText;
	mouseText.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouseText.setFont(this->font);
	mouseText.setCharacterSize(30);
	std::stringstream ss;
	ss << this->mousePosView.x << " " << this->mousePosView.y;
	mouseText.setString(ss.str());
	target->draw(mouseText);
}
