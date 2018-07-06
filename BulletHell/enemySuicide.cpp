#include "enemySuicide.h"
#include "Hero.h"
enemySuicide::enemySuicide()
{
	enemyTitle.setSize({ 12, 12 });
	enemyTitle.setOrigin(5, 5);
	speed = rand() / (float)RAND_MAX * 0.3 + 1.5;
	health = 20;
	shootFrequency = -1;
	isDieCollision = true;
}
void enemySuicide::shoot(std::vector<Bullet>& bullet, Hero& hero, std::vector<sf::Sprite>& wallTitle)
{

	shootTimer++;
	if (shootTimer < shootFrequency)
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
			bulletBuf.speed = 2;

			bullet.push_back(bulletBuf);
		}
	}
}
