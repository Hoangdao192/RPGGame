#include "PreCompile.h"
#include "State.h"

//REMOVE LATER
void State::mousePosDraw(sf::RenderTarget& target)
{
	sf::Text mouse;
	mouse.setPosition(this->mousePosView.x, this->mousePosView.y - 50);
	mouse.setCharacterSize(30);
	mouse.setFillColor(sf::Color::White);
	
	sf::Font font;
	font.loadFromFile("Fonts/Quicksand.ttf");
	mouse.setFont(font);

	std::stringstream ss;
	ss << this->mousePosView.x << ", " << this->mousePosView.y;
	mouse.setString(ss.str());

	target.draw(mouse);
}

//Constructor/Destructor

State::State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states)
{
	this->window = window;
	this->supportedKeys = supportedKeys;
	this->quit = false;
	this->states = states;
	this->paused = false;
	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;
}

State::~State()
{
}

//Accessors

const bool& State::getQuit() const
{
	return this->quit;
}

const bool State::getKeyTime()
{
	if (this->keyTime >= this->keyTimeMax)
	{
		this->keyTime = 0.f;
		return true;
	}
	return false;
}

//Functions

void State::endState()
{
	this->quit = true;
}

void State::pauseState()
{
	this->paused = true;
}

void State::unpauseState()
{
	this->paused = false;
}

void State::updateMousePosition()
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);
	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
}

void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 50.f * dt;
	}
}
