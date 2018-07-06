#pragma once
#include <SFML/Graphics.hpp>

class GameMenu
{
public:
	sf::Font font;

	sf::Text continueText;
	sf::Text restartText;
	sf::Text exitText;
	sf::RectangleShape blackShape;

	GameMenu(sf::RenderWindow& window);

	void draw(sf::RenderWindow& window);
	
	void setPosition(sf::RenderWindow& window);

	int update(sf::RenderWindow& window);
	
};
