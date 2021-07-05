#ifndef GAMESTATE_H
#define GAMESTATE_H

#include "State.h"
#include "PauseMenu.h"
#include "TileMap.h"

class PauseMenu;
class Player;
class TileMap;

class GameState :
    public State
{
private:
    //Variables
    sf::View view;
    sf::RenderTexture renderTexture;
    sf::Sprite renderSprite;

    sf::Font font;
    sf::Texture texture;
    Player* player;
    PauseMenu *pauseMenu;

    TileMap* tileMap;
    //Functions
    void initDeferredRender();
    void initView();
    void initFonts();
    void initKeybinds();
    void initTextures();
    void initPauseMenu();
    void initPlayers();
    void initTileMap();
public:
    GameState(StateData* state_data);
    virtual ~GameState();

    //Functions
    void updateView(const float& dt);
    void updatePlayerInput(const float& delta_time);
    void updateInput(const float& dt);
    void updatePauseMenuButtons();
    void update(const float& delta_time);
    void render(sf::RenderTarget* target = nullptr);
};

#endif // !GAMESTATE_H

