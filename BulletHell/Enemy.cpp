#include "Enemy.h"
#include "Hero.h"
#include "FindWay.h"
#include "Room.h"
#include "enemyPurple.h"
#include "enemySuicide.h"

void Enemy::setPosition(sf::Vector2f pos)
{
	enemyTitle.setPosition(pos);
}

void Enemy::move(Hero& hero, std::vector<Enemy*>& enemy, int n, std::vector<int>& wall, std::vector<sf::Sprite>& wallTitle, std::vector<Bullet>& bullet)
{
	int x = enemyTitle.getPosition().x;
	int y = enemyTitle.getPosition().y;

	
	curentPos = (y / 64 * 200) + x / 64;
		
	updateHeroPos(hero, wallTitle);
	int end;
	if (!isHeroTexPointMiddleCrossing)
		end = (int)HeroPointMiddle.y / 64 * 200 + (int)HeroPointMiddle.x / 64;
	else if (!isHeroTexPointDownCrossing)
		end = (int)HeroPointDown.y / 64 * 200 + (int)HeroPointDown.x / 64;
	else if (!isHeroTexPointUpCrossing)
		end = (int)HeroPointUp.y / 64 * 200 + (int)HeroPointUp.x / 64;
	
	int start = curentPos;
	int xToCenter;
	int yToCenter;
	if (start != end)
	{
		FindWay Way(start);
		Way.findWay(Way.start, end, wall);

		int pos = 0;
		pos = Way.way[Way.way.size() - 1];
		xToCenter = pos % 200 * 64 - x + 32;
		yToCenter = pos / 200 * 64 - y + 32;
	}
	else {
		if (!isHeroTexPointMiddleCrossing)
		{
			xToCenter = hero.HeroTitle.getPosition().x - x;
			yToCenter = hero.HeroTitle.getPosition().y - y;
		}
		else if (!isHeroTexPointDownCrossing)
		{
			xToCenter = HeroPointDown.x - x;
			yToCenter = HeroPointDown.y - y;
		}
		else if (!isHeroTexPointUpCrossing)
		{
			xToCenter = HeroPointUp.x - x;
			yToCenter = HeroPointUp.y - y;
		}
	}

		

	enemyTitle.move((speed * (xToCenter < 0 ? -1 : (xToCenter > 0 ? 1 : 0))), 0);
	enemyTitle.move(0, speed * (yToCenter < 0 ? -1 : (yToCenter > 0 ? 1 : 0)));
	
	
	for (int i = 0; i < bullet.size(); i++)
	{
		if (enemyTitle.getGlobalBounds().intersects(bullet[i].bulletTitle.getGlobalBounds()) && bullet[i].isHero == true)
		{
			health -= 30;
			bullet.erase(bullet.begin() + i);
		}
	}
	 if (health <= 0)
		enemy.erase(enemy.begin() + n);
}

int Enemy::isClear(Hero& hero, std::vector<sf::Sprite>& wallTitle)
{
	sf::Vector2f direction;
	updateHeroPos(hero, wallTitle);
	
	if (!isHeroTexPointMiddleCrossing )
		direction = HeroPointMiddle - enemyTitle.getPosition();
	else if (!isHeroTexPointUpCrossing)
		direction = HeroPointUp - enemyTitle.getPosition();
	else if (!isHeroTexPointDownCrossing)
		direction = HeroPointDown - enemyTitle.getPosition();
	
	float length = sqrt(pow(direction.x, 2) + pow(direction.y, 2));
	if (abs(length) > 200)
		return 1;
	
	direction.x *= 4 / length; 
	direction.y *= 4 / length;

	sf::Vector2f bulletPos = enemyTitle.getPosition();
	for (int i = 0; i <= length; i += 4)
	{		for (int j = 0; j < wallTitle.size(); j++)
		{
			if (wallTitle[j].getGlobalBounds().contains(bulletPos))
				return 1;
		}
		bulletPos += direction;
	}
	return 0;
}

void Enemy::updateHeroPos(Hero& hero, std::vector<sf::Sprite>& wallTitle)
{
	HeroPointUp = { hero.HeroTitle.getPosition().x, hero.HeroTitle.getPosition().y - hero.HeroTitle.getGlobalBounds().height / 2 };
	HeroPointMiddle = { hero.HeroTitle.getPosition().x, hero.HeroTitle.getPosition().y };
	HeroPointDown = { hero.HeroTitle.getPosition().x, hero.HeroTitle.getPosition().y + hero.HeroTitle.getGlobalBounds().height / 2 };

	isHeroTexPointDownCrossing = false;
	isHeroTexPointMiddleCrossing = false;
	isHeroTexPointUpCrossing = false;
	for (int i = 0; i < wallTitle.size(); i++)
	{
		if (wallTitle[i].getGlobalBounds().contains(HeroPointUp))
			isHeroTexPointUpCrossing = true;
		
		if (wallTitle[i].getGlobalBounds().contains(HeroPointMiddle))
			isHeroTexPointMiddleCrossing = true;
		if (wallTitle[i].getGlobalBounds().contains(HeroPointDown))
			isHeroTexPointDownCrossing = true;
	}
}


