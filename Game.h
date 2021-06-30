#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	//	Variables
	GraphicSettings graphicSettings;
	StateData stateData;
	sf::RenderWindow *window;
	sf::Event sfEvent;

	sf::Clock dtClock;
	float deltaTime;

	std::stack<State*>	states;

	std::map < std::string , int > supportedKeys;

	float gridSize;

	//	Intialization
	void initVariables();
	void initGraphicSettings();
	void initStateData();
	void initWindow();
	void initStates();
	void initKeys();
public:
	Game();
	virtual ~Game();

	/*Functions*/
	//Regular
	void endApplication();

	//Update
	void update();
	void updateSFMLEvents();
	void updateDeltaTime();

	//Render
	void render();

	//Core
	void run();

};

#endif // !GAME_H

