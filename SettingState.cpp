#include "PreCompile.h"
#include "SettingState.h"

//Initializer

void SettingState::initVariables()
{
	this->videoModes = sf::VideoMode::getFullscreenModes();
}

void SettingState::initBackground()
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

void SettingState::initFonts()
{
	if (!this->font.loadFromFile("Fonts/Quicksand.ttf"))
	{
		throw("Error: MainMenuState->initFonts: could not load font Fonts/Quicksand.ttf");
	}

}

void SettingState::initKeybinds()
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

void SettingState::initGui()
{
	this->buttons["BACK"] = new Button(300, 420, 150, 50, &this->font,
		"Back", 20,
		sf::Color(255, 255, 255, 200),
		sf::Color(0, 255, 255, 255),
		sf::Color(250, 250, 20, 255),
		sf::Color(100, 100, 100, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	this->buttons["APPLY"] = new Button(100, 420, 150, 50, &this->font,
		"Apply", 20,
		sf::Color(255, 255, 255, 200),
		sf::Color(0, 255, 255, 255),
		sf::Color(250, 250, 20, 255),
		sf::Color(100, 100, 100, 200),
		sf::Color(150, 150, 150, 255),
		sf::Color(20, 20, 20, 200));

	std::vector<std::string> videomode_str;
	for (auto& i : this->videoModes)
	{
		videomode_str.push_back(std::to_string(i.width) + " x " + std::to_string(i.height));
	}

	this->dropDownLists["RESOLUTION"] = new DropDownList(350, 100, 150, 50, this->font, videomode_str.data(), videomode_str.size());
}

void SettingState::initText()
{
	this->optionsText.setFont(this->font);
	this->optionsText.setPosition(sf::Vector2f(100.f, 100.f));
	this->optionsText.setCharacterSize(50);
	this->optionsText.setFillColor(sf::Color(255, 255, 255, 200));

	this->optionsText.setString(
		"Resolution \nFullscreen \nVsync \nAntialising \n"
	);
}


//Constructor/Descontructor

SettingState::SettingState(StateData* state_data)
	:State(state_data)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initGui();
	this->initText();
}

SettingState::~SettingState()
{
	for (auto& it: this->buttons)
	{
		delete it.second;
	}

	for (auto& it : this->dropDownLists)
	{
		delete it.second;
	}
}

//Accessors

//Functions

void SettingState::updateInput(const float& delta_time)
{
	//Update player input (convert int to enum Key)
}

void SettingState::updateGui(const float& delta_time)
{
	/*Update all the gui elements in the state and handles their functionality*/

	//Buttons
	std::map<std::string, Button*>::iterator it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
	{
		it->second->update(this->mousePosView);
	}

	//Buttons funtionality
	//Quit setting
	if (this->buttons["BACK"]->isPressed())
	{
		this->endState();
	}

	//Apply selected settings
	if (this->buttons["APPLY"]->isPressed())
	{
		this->stateData->gfxSettings->resolution = this->videoModes.at(this->dropDownLists["RESOLUTION"]->getActiveElementId());
		this->window->create(this->stateData->gfxSettings->resolution, this->stateData->gfxSettings->title);
	}

	//Dropdown lists
	for (auto& it : this->dropDownLists)
	{
		it.second->update(this->mousePosView, delta_time);
	}
	//Dropdown lists funtionality
	
}

void SettingState::update(const float& delta_time)
{
	this->updateMousePosition();
	this->updateInput(delta_time);
	this->updateGui(delta_time);
}

void SettingState::renderGui(sf::RenderTarget& target)
{
	//Buttons
	std::map<std::string, Button*>::iterator it = this->buttons.begin();
	for (; it != this->buttons.end(); ++it)
	{
		it->second->render(target);
	}

	//Drop-down lists
	for (auto& it : this->dropDownLists)
	{
		it.second->render(target);
	}
}

void SettingState::render(sf::RenderTarget* target)
{
	if (!target)
	{
		std::cout << "\ntarget not set. set to default = window";
		target = this->window;
	}

	target->draw(this->background);

	this->renderGui(*target);

	target->draw(this->optionsText);

	this->mousePosDraw(*target);
}