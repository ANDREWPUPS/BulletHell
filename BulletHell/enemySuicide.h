#pragma once
#include "Enemy.h"


class enemySuicide : public Enemy
{
public:
	enemySuicide();

	void shoot(std::vector<Bullet>& bullet, Hero& hero, std::vector<sf::Sprite>& wallTitle);
};
