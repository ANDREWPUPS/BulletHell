#pragma once
#include <SFML/Graphics.hpp>
#include "Level.h"
#include"Hero.h"

class MiniMap
{
public:
	sf::RectangleShape blackShape;
	sf::Text marker;
	sf::Font font;
	sf::Vector2f mousePosOld;
	int n = 0;

	MiniMap();
	
	void draw(Level& level, Hero& hero, sf::RenderWindow& window);
	
	void update(sf::RenderWindow& window, sf::View& minimapview);
	

};