#include "enemyPurple.h"
#include "Hero.h"
enemyPurple::enemyPurple()
{
	enemyTitle.setSize({ 20, 20 });
	enemyTitle.setOrigin(10, 10);
	speed = rand() / (float)RAND_MAX * 0.2 + 0.4;
	health = 100;
	shootFrequency = 60;
}
void enemyPurple::shoot(std::vector<Bullet>& bullet, Hero& hero, std::vector<sf::Sprite>& wallTitle)
{
	
	shootTimer++;
	if (shootTimer > shootFrequency)
	{
		if (isClear(hero, wallTitle) == 0)
		{

			Bullet bulletBuf;
			shootTimer = 0;
			bulletBuf.bulletTitle.setPosition(enemyTitle.getPosition());
			bulletBuf.direction = hero.HeroTitle.getPosition() - enemyTitle.getPosition();
			float length = sqrt(pow(bulletBuf.direction.x, 2) + pow(bulletBuf.direction.y, 2));
			bulletBuf.direction.x /= length;
			bulletBuf.direction.y /= length;
			bulletBuf.speed = 3.5;

			bullet.push_back(bulletBuf);
		}
	}
}
