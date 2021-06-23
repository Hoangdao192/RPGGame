#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"

#include "GUI.h"
using namespace Gui;


class EditorState
	:public State
{
private:
    //Variables
    sf::Font font;

    std::map<std::string, Button*> buttons;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();

public:
    EditorState(sf::RenderWindow* window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& delta_time);
    void updateButtons();
    void update(const float& delta_time);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // !EDITORSTATE_H
