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
    sf::Text cursorText;
    sf::Font font;

    std::map<std::string, Button*> buttons;

    TileMap* tileMap;

    sf::RectangleShape sidebar;

    sf::IntRect textureRect;
    sf::RectangleShape selectorRect;
    TextureSelector* textureSelector;

    //Functions
    void initVariables();
    void initBackground();
    void initFonts();
    void initText();
    void initKeybinds();
    void initButtons();
    void initGui();
    void initPauseMenu();
    void initTileMap();

public:
    EditorState(StateData* state_data);
    virtual ~EditorState();

    //Functions
    void updateInput(const float& delta_time);
    void updateEditorInput(const float& dt);
    void updateButtons();
    void updateGui(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& delta_time);
    void renderButtons(sf::RenderTarget& target);
    void renderGui(sf::RenderTarget& target);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // !EDITORSTATE_H
