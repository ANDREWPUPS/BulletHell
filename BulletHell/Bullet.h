#pragma once
#include <SFML/Graphics.hpp>

class Bullet
{
public:
	float speed;
	sf::Vector2f direction;
	sf::CircleShape bulletTitle;
	bool isHero = false;
	int damage = 30;
	
	Bullet();
	
	int Bullet::move(std::vector<sf::Sprite>& wallTitle);
};