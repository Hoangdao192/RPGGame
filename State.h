#ifndef STATE_H
#define STATE_H

#include "Player.h"

class State
{
private:

protected:
	std::stack<State*>* states;

	sf::RenderWindow* window;
	std::map<std::string, int>* supportedKeys;
	std::map<std::string, int> keybinds;
	bool quit;
	bool paused;
	float keyTime;
	float keyTimeMax;

	sf::Vector2i mousePosScreen;
	sf::Vector2i mousePosWindow;
	sf::Vector2f mousePosView;

	//Resources
	std::map<std::string, sf::Texture> textures;

	//Functions
	virtual void initKeybinds() = 0;

public:
	State(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
	virtual ~State();

	//Accessors
	const bool& getQuit() const;
	const bool getKeyTime();

	//	Functions
	void endState();
	void pauseState();
	void unpauseState();

	virtual void updateInput(const float& delta_time) = 0;
	virtual void updateMousePosition();
	virtual void updateKeyTime(const float& dt);
	virtual void update(const float& delta_time) = 0;
	virtual void render(sf::RenderTarget* target = nullptr) = 0;

	//REMOVE LATER
	void mousePosDraw(sf::RenderTarget& target);
};


#endif
