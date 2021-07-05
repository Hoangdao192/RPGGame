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

State::State(StateData* state_data)
{
	this->stateData = state_data;
	this->window = state_data->window;
	this->supportedKeys = state_data->supportedKeys;
	this->quit = false;
	this->states = state_data->states;
	this->paused = false;
	this->keyTime = 0.f;
	this->keyTimeMax = 10.f;
	this->gridSize = state_data->gridSize;
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

void State::updateMousePosition(sf::View* view)
{
	this->mousePosScreen = sf::Mouse::getPosition();
	this->mousePosWindow = sf::Mouse::getPosition(*this->window);

	if (view) { this->window->setView(*view); }

	this->mousePosView = this->window->mapPixelToCoords(sf::Mouse::getPosition(*this->window));
	this->mousePosGrid =
		sf::Vector2u(
			static_cast<unsigned> (this->mousePosView.x) / static_cast<unsigned> (this->gridSize),
			static_cast<unsigned> (this->mousePosView.y) / static_cast<unsigned> (this->gridSize)
		);

	this->window->setView(this->window->getDefaultView());
}

void State::updateKeyTime(const float& dt)
{
	if (this->keyTime < this->keyTimeMax)
	{
		this->keyTime += 50.f * dt;
	}
}
