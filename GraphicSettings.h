#ifndef GRAPHICSETTINGS_H
#define GRAPHICSETTINGS_H

class GraphicSettings
{
public:
	GraphicSettings();

	//Variables
	std::string title;
	sf::VideoMode resolution;
	bool fullscreen;
	bool vsync;
	unsigned frameRateLimit;
	sf::ContextSettings contextSettings;
	std::vector<sf::VideoMode> videoModes;

	//Functions
	void saveToFile(const std::string path);
	bool loadFromFile(const std::string path);
};

#endif // !GRAPHICSETTINGS_H
