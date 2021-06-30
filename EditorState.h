#ifndef EDITORSTATE_H
#define EDITORSTATE_H

#include "State.h"
#include "GUI.h"
#include "PauseMenu.h"
#include "TileMap.h"


using namespace Gui;

class State;
class PauseMenu;
class TileMap;

class EditorState
	:public State
{
private:
    //Variables
    PauseMenu* pauseMenu;
    sf::Font font;

    std::map<std::string, Button*> buttons;

    TileMap* tileMap;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initKeybinds();
    void initButtons();
    void initPauseMenu();
    void initTileMap();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& delta_time);
    void updateButtons();
    void updatePauseMenuButtons();
    void update(const float& delta_time);
    void renderButtons(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // !EDITORSTATE_H
