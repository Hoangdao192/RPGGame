#include "PreCompile.h"
#include "Game.h"

//	Static functions


//	Intialize functions

void Game::initVariables()
{
    this->window = NULL;
    this->deltaTime = 0.f;

    this->gridSize = 100;
}

void Game::initGraphicSettings()
{
    this->graphicSettings.loadFromFile("Config/graphics.ini");
}

void Game::initStateData()
{
    this->stateData.window = this->window;
    this->stateData.gfxSettings = &this->graphicSettings;
    this->stateData.supportedKeys = &this->supportedKeys;
    this->stateData.states = &this->states;
    this->stateData.gridSize = this->gridSize;
}

void Game::initWindow()
{
    /*Create a SFML Window using options from a Window.ini file.*/
    if (this->graphicSettings.fullscreen)
    {
        // Create fullscreen SFML window
        this->window = new sf::RenderWindow(
            this->graphicSettings.resolution, 
            this->graphicSettings.title, sf::Style::Fullscreen, 
            this->graphicSettings.contextSettings);
    }
    else
    {
        // Create default SFML window and not resizeable
        this->window = new sf::RenderWindow(
            this->graphicSettings.resolution, 
            this->graphicSettings.title, sf::Style::Titlebar | sf::Style::Close, 
            this->graphicSettings.contextSettings);
    }
	
    this->window->setFramerateLimit(this->graphicSettings.frameRateLimit);
    this->window->setVerticalSyncEnabled(this->graphicSettings.vsync);
}

void Game::initStates()
{
    this->states.push(new MainMenuState(&this->stateData));
    //this->states.push(new GameState(this->window, &this->supportedKeys));
}

void Game::initKeys()
{
    std::fstream file("Config/supported_keys.ini", std::ios::in);
    if (!file.is_open())
    {
        std::cout << "\nError: Cannot load file Config/supported_keys.ini";
    }
    while (!file.eof())
    {
        std::string key;
        int key_value;
        file >> key >> key_value;
        std::cout << "\n" << key << " " << key_value;
        this->supportedKeys[key] = key_value;
    }
    file.close();
}

//	Construcstors/Destrucstors
Game::Game()
{
    this->initVariables();
    this->initGraphicSettings();
    this->initWindow();
    this->initKeys();
    this->initStateData();
    this->initStates();
}

Game::~Game()
{
	delete this->window;
    while (!this->states.empty())
    {
        delete this->states.top();
        this->states.pop();
    }

    //Save graphic setting
    graphicSettings.saveToFile("Config/graphics.ini");
}


//Functions
void Game::endApplication()
{
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty() && this->window->hasFocus())
    {
        this->states.top()->update(deltaTime);
        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else if(this->states.empty())
        //Applicaiton end
    {
        this->endApplication();
        this->window->close();
    }
}

void Game::updateSFMLEvents()
{
    while (this->window->pollEvent(sfEvent))
    {
        if (sfEvent.type == sf::Event::Closed)
        {
            this->window->close();
        }
    }
}

void Game::updateDeltaTime()
{
    /*Update the deltaTime variable with the time it takes to update and render one frame.*/
    this->deltaTime = this->dtClock.restart().asSeconds();

    //system("cls");
   // std::cout << this->deltaTime;
}

void Game::render()
{
    this->window->clear();

    //  Render items
    if (!this->states.empty())
    {
        this->states.top()->render(window);
    }

    this->window->display();
}

void Game::run()
{
    while (this->window->isOpen())
    {
        this->updateDeltaTime();
        this->update();
        this->render();
    }
}
