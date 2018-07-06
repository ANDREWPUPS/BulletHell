#pragma once
#include <SFML/Graphics.hpp>
#include "Bullet.h"
class Hero;
class Room;
class Enemy
{
public:
	
	sf::RectangleShape  enemyTitle;
	float speed;
	int health;
	int shootFrequency;
	int shootTimer = 0;
	int curentPos;
	int stayTimer = 0;
	bool isStay = false;
	bool isDieCollision = false;

	bool isHeroTexPointUpCrossing = false;
	bool isHeroTexPointMiddleCrossing = false;
	bool isHeroTexPointDownCrossing = false;
	sf::Vector2f HeroPointUp ;
	sf::Vector2f HeroPointMiddle ;
	sf::Vector2f HeroPointDown ;
	
	
	
	virtual void shoot(std::vector<Bullet>& bullet, Hero& hero, std::vector<sf::Sprite>& wallTitle) = 0;
	
	void setPosition(sf::Vector2f pos);

	void move(Hero& hero, std::vector<Enemy*>& enemy, int n, std::vector<int>& wall, std::vector<sf::Sprite>& wallTitle, std::vector<Bullet>& bullet);

	int isClear( Hero& hero, std::vector<sf::Sprite>& wallTitle);

	void Enemy::updateHeroPos(Hero& hero, std::vector<sf::Sprite>& wallTitle);

};