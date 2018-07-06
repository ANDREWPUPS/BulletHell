#pragma once
#include <SFML/Graphics.hpp>

class EndMenu
{
public:
	sf::Font font;

	sf::Text messageText;
	sf::Text restartText;
	sf::Text exitText;
	sf::RectangleShape blackShape;

	EndMenu(sf::RenderWindow& window);
	
	void draw(sf::RenderWindow& window);
	
	void setPosition(sf::RenderWindow& window);

	int update(sf::RenderWindow& window);
	
};
