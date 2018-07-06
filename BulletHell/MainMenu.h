#pragma once
#include <SFML/Graphics.hpp>

class MainMenu
{
public:
	sf::Font font;

	sf::Text playText;
	sf::Text exitText;

	MainMenu(sf::RenderWindow& window);


	void draw(sf::RenderWindow& window);
	
	void setPosition(sf::RenderWindow& window);

	int update(sf::RenderWindow& window);
	
};