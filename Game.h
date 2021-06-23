#ifndef GAME_H
#define GAME_H

#include "MainMenuState.h"

class Game
{
private:
	//	Variables
	sf::RenderWindow *window;
	sf::Event sfEvent;
	std::vector<sf::VideoMode> videoModes;
	sf::ContextSettings windowSettings;
	bool fullscreen;

	sf::Clock dtClock;
	float deltaTime;

	std::stack<State*>	states;

	std::map < std::string , int > supportedKeys;

	//	Intialization
	void initVariables();
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

