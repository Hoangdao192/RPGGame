#include "PreCompile.h"
#include "Game.h"

//	Static functions


//	Intialize functions

void Game::initVariables()
{
    this->window = NULL;
    this->fullscreen = false;

    this->deltaTime = 0.f;
    
}

void Game::initWindow()
{
    /*Create a SFML Window using options from a Window.ini file.*/

    std::fstream file("Config/window.ini", std::ios::in);
    this->videoModes = sf::VideoMode::getFullscreenModes();

    //  Default values
    std::string title = "None";
    sf::VideoMode window_bounds = sf::VideoMode::getDesktopMode();
    bool fullscreen = false;
    unsigned framerate_limit = 120;
    bool vertical_sync_enabled = false;
    unsigned int antialiasing_level = 0;

    //  Read from file
    if (file.is_open())
    {
        std::getline(file, title);
        file >> window_bounds.width >> window_bounds.height;
        file >> fullscreen;
        file >> framerate_limit;
        file >> vertical_sync_enabled;
        file >> antialiasing_level;
    }
    else
    {
        std::cout << "Cannot open file Config/window.ini";
    }
    file.close();

    //  Create SFML Window
    this->fullscreen = fullscreen;
    this->windowSettings.antialiasingLevel = antialiasing_level;
    if (this->fullscreen)
    {
        // Create fullscreen SFML window
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Fullscreen, this->windowSettings);
    }
    else
    {
        // Create default SFML window and not resizeable
        this->window = new sf::RenderWindow(window_bounds, title, sf::Style::Titlebar | sf::Style::Close, this->windowSettings);
    }
	
    this->window->setFramerateLimit(framerate_limit);
    this->window->setVerticalSyncEnabled(vertical_sync_enabled);
}

void Game::initStates()
{
    this->states.push(new MainMenuState(this->window, &this->supportedKeys, &this->states));
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
    this->initWindow();
    this->initKeys();
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
}


//Functions
void Game::endApplication()
{
}

void Game::update()
{
    this->updateSFMLEvents();

    if (!this->states.empty())
    {
        this->states.top()->update(deltaTime);
        if (this->states.top()->getQuit())
        {
            this->states.top()->endState();
            delete this->states.top();
            this->states.pop();
        }
    }
    else
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
