#ifndef STATE_H
#define STATE_H

#include "Player.h"
#include "GraphicSettings.h"

class Player;
class GraphicsSettings;

class State;

class StateData
{
public:
	StateData() 
	{
		this->gridSize = 0;
		this->window = nullptr;
		this->gfxSettings = nullptr;
		this->supportedKeys = nullptr;
		this->states = nullptr;
	}

	//Variable
	float gridSize;
	sf::RenderWindow* window;
	GraphicSettings* gfxSettings;
	std::map<std::string, int>* supportedKeys;
	std::stack<State*>* states;

};

class State
{
private:

protected:
	StateData* stateData;
	std::stack<State*>* states;

	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keyTime;
	float keyTimeMax;
	float gridSize;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;
	sf::Vector2u mousePosGrid;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(StateData* state_data);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeyTime();

	//	Functions
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateInput(const float& delta_time) = 0;
	virtual void updateMousePosition(sf::View* view = nullptr);
	virtual void updateKeyTime(const float& dt);
	virtual void update(const float& delta_time) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	//REMOVE LATER
	void mousePosDraw(sf::RenderTarget& target);
};


#endif

