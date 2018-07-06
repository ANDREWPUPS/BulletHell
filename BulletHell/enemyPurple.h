#pragma once
#include "Enemy.h"


class enemyPurple : public Enemy
{
public:
	enemyPurple();
	
	void shoot(std::vector<Bullet>& bullet, Hero& hero, std::vector<sf::Sprite>& wallTitle);
};
