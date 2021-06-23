#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"

class GameState :
    public State
{
private:
    //Variables
    sf::Font font;
    sf::Texture texture;
    Player* player;
    PauseMenu *pauseMenu;

    //Functions
    void initFonts();
    void initKeybinds();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
public:
    GameState(sf::RenderWindow *window, std::map<std::string, int>* supportedKeys, std::stack<State*>* states);
    virtual ~GameState();

    //Functions
    void updatePlayerInput(const float& delta_time);
    void updateInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& delta_time);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // !GAMESTATE_H

