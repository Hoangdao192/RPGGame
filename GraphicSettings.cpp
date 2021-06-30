#include "PreCompile.h"
#include "GraphicSettings.h"

//Constructor

GraphicSettings::GraphicSettings()
{
    this->title = "UNINITIALIZED";
    this->resolution = sf::VideoMode::getDesktopMode();
    this->fullscreen = false;
    this->frameRateLimit = 120;
    this->vsync = false;
    this->contextSettings.antialiasingLevel = 0;
    this->videoModes = sf::VideoMode::getFullscreenModes();
}

//Functions

void GraphicSettings::saveToFile(const std::string path)
{
    std::fstream file(path, std::ios::out);
    //  Read from file
    if (file.is_open())
    {
        file << this->title << "\n";
        file << this->resolution.width << " " << this->resolution.height << "\n";
        file << this->fullscreen << "\n";
        file << this->frameRateLimit << "\n";
        file << this->vsync << "\n";
        file << contextSettings.antialiasingLevel;
    }
}

bool GraphicSettings::loadFromFile(const std::string path)
{
    bool ret = false;

    std::fstream file(path, std::ios::in);
    //  Read from file
    if (file.is_open())
    {
        ret = true;
        std::getline(file, this->title);
        file >> this->resolution.width >> this->resolution.height;
        file >> this->fullscreen;
        file >> this->frameRateLimit;
        file >> this->vsync;
        file >> contextSettings.antialiasingLevel;
    }
    else
    {
        std::cout << "Cannot open file Config/window.ini";
    }
    file.close();

    return ret;
}
