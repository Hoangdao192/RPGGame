#ifndef MAINMENUSTATE_H
#define MAINMENUSTATE_H

#include "GameState.h"
#include "EditorState.h"
#include "SettingState.h"

#include "GUI.h"
using namespace Gui;

class MainMenuState
	: public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, Button*> buttons;

    //Initializer
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    MainMenuState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~MainMenuState();

    //Functions
    void updateInput(const float& delta_time);
    void updateButtons();
    void update(const float& delta_time);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // ! MAINMENUSTATE_H

