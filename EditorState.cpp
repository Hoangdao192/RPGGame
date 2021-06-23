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

//Constructor/Destructor

EditorState::EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
	:State(window, supportedKeys, states)
{
	this->initVariables();
	this->initBackground();
	this->initFonts();
	this->initKeybinds();
	this->initButtons();
}

EditorState::~EditorState()
{
	for (std::map<std::string, Button*>::iterator it = buttons.begin(); it != buttons.end(); ++it)
	{
		delete it->second;
	}
}

//Functions

void EditorState::updateInput(const float& delta_time)
{
	//Update player input (convert int to enum Key)
	if (sf::Keyboard::isKeyPressed((sf::Keyboard::Key)this->keybinds.at("CLOSE")))
	{
		this->endState();
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

void EditorState::update(const float& delta_time)
{
	this->updateMousePosition();
	this->updateInput(delta_time);
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
