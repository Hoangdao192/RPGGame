#include "PreCompile.h"
#include "MainMenuState.h"

//Initializer

void MainMenuState::initVariables()
{
}

void MainMenuState::initBackground()
{
	this->background.setSize((sf::Vector2f)this->window->getSize());

	if (!this->backgroundTexture.loadFromFile("Resources/Images/Backgrounds/bg1.jpg"))
	{
		throw "ERROR::MAINMENUSTATE::FAILED_TO_LOAD_Resources/Images/Backgrounds/bg1.jpg";
	}
	else
	{
		this->background.setTexture(&this->backgroundTexture);
	}
}

void MainMenuState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Quicksand.ttf"))
	{
		throw("Error: MainMenuState->initFonts: could not load font Fonts/Quicksand.ttf");
	}

}

void MainMenuState::initKeybinds()
{
	std::fstream file("Config/mainmenustate_keybinds.ini", std::ios::in);
	if (!file.is_open())
	{
		std::cout << "\nError: Cannot load file Config/mainmenustate_keybinds.ini";
	}

	while (!file.eof())
	{
		std::string keybind, keybind_value;
		file >> keybind >> keybind_value;
		this->keybinds[keybind] = this->supportedKeys->at(keybind_value);
	}

	file.close();
}

void MainMenuState::initButtons() 
{
	this->buttons["GAME_STATE"] = new Button(100, 100, 150, 50, &this->font,
		"New game", 20,
		sf::Color(255, 255, 255, 200),
		sf::Color(0, 255, 255, 255),
		sf::Color(250, 250, 20, 255),
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	this->buttons["SETTING_STATE"] = new Button(100, 170, 150, 50, &this->font,
		"Settings", 20,
		sf::Color(255, 255, 255, 200),
		sf::Color(0, 255, 255, 255),
		sf::Color(250, 250, 20, 255),
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	this->buttons["EDITOR_STATE"] = new Button(100, 240, 150, 50, &this->font,
		"Editor", 20,
		sf::Color(255, 255, 255, 200),
		sf::Color(0, 255, 255, 255),
		sf::Color(250, 250, 20, 255),
		sf::Color(70, 70, 70, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	this->buttons["EXIT_STATE"] = new Button(100, 310, 150, 50, &this->font,
		"Quit", 20,
		sf::Color(255, 255, 255, 200),
		sf::Color(0, 255, 255, 255),
		sf::Color(250, 250, 20, 255),
		sf::Color(100, 100, 100, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));
}

//Constructor/Destructor

MainMenuState::MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

MainMenuState::~MainMenuState()
{
	for (std::map<std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions

void MainMenuState::updateInput(const float& delta_time)
{
	//Update player input (convert int to enum Key)
}

void MainMenuState::updateButtons()
{
	/*Update all the buttons in the state and handles their functionality*/
	
	std::map<std::string, Button*>::iterator it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
	{
		it->second->update(this->mousePosView);
	}

	//New game
	if (this->buttons["GAME_STATE"]->isPressed())
	{
		this->states->push(new GameState(this->window, this->supportedKeys, this->states));
	}

	//Setting
	if (this->buttons["SETTING_STATE"]->isPressed())
	{
		this->states->push(new SettingState(this->window, this->supportedKeys, this->states));
	}

	//Editor
	if (this->buttons["EDITOR_STATE"]->isPressed())
	{
		this->states->push(new EditorState(this->window, this->supportedKeys, this->states));
	}

	//Quit the game
	if (this->buttons["EXIT_STATE"]->isPressed())
	{
		this->endState();
	}
}

void MainMenuState::update(const float& delta_time)
{
	this->updateMousePosition();
	this->updateInput(delta_time);
	this->updateButtons();
}
	
void MainMenuState::renderButtons(sf::RenderTarget& target)
{
	std::map<std::string, Button*>::iterator it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
	{
		it->second->render(target);
	}
}

void MainMenuState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		std::cout << "\ntarget not set. set to default = window";
		target = this->window;
	}

	target->draw(this->background);

	this->renderButtons(*target);

	this->mousePosDraw(*target);
}