#pragma once
#include <SFML/Graphics.hpp>
#include "Enemy.h"
#include "Animation.h"
class Hero
{
public:

	//sf::CircleShape HeroTitle;
	sf::Texture HeroTitleTex;
	sf::Sprite HeroTitle;
	sf::RectangleShape HeroGun;
	float HeroSpeed = 2;
	int health = 100;
	int isInvincible = false;
	int invincibleTimer = 0;
	int shootingTimer = 1000;
	bool isDrawindUnderLevel = false;
	bool isStay;
	bool isTeleporting = false;
	std::string teleportDirection;
	std::string mouseDirection;
	int teleportTimer = 0;

	sf::Vector2f HeroTexPointUp;
	sf::Vector2f HeroTexPointMiddle;
	sf::Vector2f HeroTexPointDown;
	bool isHeroTexPointUpCrossing = false;
	bool isHeroTexPointMiddleCrossing = false;
	bool isHeroTexPointDownCrossing = false;
	
	
	Animation HeroAnimationFrontWalk;
	Animation HeroAnimationBackWalk;
	Animation HeroAnimationRightWalk;
	Animation HeroAnimationRightUpWalk;
	Animation HeroAnimationRightDownWalk;
	Animation HeroAnimationFrontStay;
	Animation HeroAnimationBackStay;
	Animation HeroAnimationRightStay;
	Animation HeroAnimationRightUpStay;
	Animation HeroAnimationRightDownStay;
	Hero(sf::RenderWindow& window);

	void move(std::vector<Room>& allRoom, sf::RenderWindow& window);

	void collision(std::vector<Enemy*>& enemy, std::vector<Bullet>& bullet);

	void shoot(sf::RenderWindow& window, std::vector<Bullet>& bullet);

	void draw(sf::RenderWindow& window);

	void updateMouseDirection(sf::RenderWindow& window);

	void checkCrossing(std::vector <Room>& allRooms, std::string direction);

	void setHeroAnimation();
};
