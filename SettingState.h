#ifndef SETTINGSTATE_H
#define SETTINGSTATE_H

#include "State.h"
#include "GUI.h"
using namespace Gui;

class SettingState
	:public State
{
private:
    //Variables
    sf::Texture backgroundTexture;
    sf::RectangleShape background;
    sf::Font font;

    std::map<std::string, Button*> buttons;
    std::map<std::string, DropDownList*> dropDownLists; 

    sf::Text optionsText;

    std::vector<sf::VideoMode> videoModes;

    //Initializer
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initGui();
    void initText();

public:
	SettingState(StateData* state_data);
	virtual ~SettingState();

	//Accessors

	//Functions
    void updateInput(const float& delta_time);
    void updateGui(const float& delta_time);
    void update(const float& delta_time);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // !SETTINGSTATE_H
