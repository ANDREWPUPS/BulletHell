#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Animation.h"

class Spawner {
public:
	sf::Sprite spawnerSprite;
	Animation spawnerAnimation;
	Spawner();
	Spawner( Room& heroCurrentRoom, std::vector<int>& allWall);
		

	void update(std::vector<Enemy*>& Allenemy);
		
	

	void draw(sf::RenderWindow& window);
	

	bool active = true;
private:
	std::vector<Enemy*> enemies;
	sf::Clock timer;
	float radius = 5;
};