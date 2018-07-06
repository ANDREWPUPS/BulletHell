#include "Hero.h"
#include "Room.h"
#include <iostream>
Hero::Hero(sf::RenderWindow& window)
{
	HeroTitle.setPosition(6600, 6800);
	HeroAnimationFrontWalk = Animation("Resourses/Sprites/Animation/Player/Front_Walk.png");
	HeroAnimationBackWalk = Animation("Resourses/Sprites/Animation/Player/Back_Walk.png");
	HeroAnimationRightWalk = Animation("Resourses/Sprites/Animation/Player/Side_Walk.png");
	HeroAnimationRightUpWalk = Animation("Resourses/Sprites/Animation/Player/BackDiag_Walk.png");
	HeroAnimationRightDownWalk = Animation("Resourses/Sprites/Animation/Player/FrontDiag_Walk.png");
	HeroAnimationFrontStay= Animation("Resourses/Sprites/Animation/Player/Front_Idle.png");
	HeroAnimationBackStay = Animation("Resourses/Sprites/Animation/Player/Back_Idle.png");
	HeroAnimationRightStay = Animation("Resourses/Sprites/Animation/Player/Side_Idle.png");
	HeroAnimationRightUpStay = Animation("Resourses/Sprites/Animation/Player/BackDiag_Idle.png");
	HeroAnimationRightDownStay = Animation("Resourses/Sprites/Animation/Player/FrontDiag_Idle.png");
	//HeroGun.setSize({ (float)(HeroTitle.getRadius()), 3.f});
	//HeroGun.setOrigin(0, 1.5);
	//HeroGun.setFillColor(sf::Color::Red);
}
void Hero::move(std::vector<Room>& allRoom, sf::RenderWindow& window)
{
	isStay = true;
	
	if (isTeleporting == false)

	{
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			isTeleporting = true;
			teleportDirection = "Up";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			isTeleporting = true;
			teleportDirection = "Down";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			isTeleporting = true;
			teleportDirection = "Left";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			isTeleporting = true;
			teleportDirection = "Right";
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W) && sf::Keyboard::isKeyPressed(sf::Keyboard::D) && sf::Keyboard::isKeyPressed(sf::Keyboard::Space))
		{
			isTeleporting = true;
			teleportDirection = "RightUp";
		}


		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
		{
			HeroTitle.move(-HeroSpeed, 0);
			isStay = false;
			
			checkCrossing(allRoom, "Left");

			if (isHeroTexPointUpCrossing == true && isHeroTexPointMiddleCrossing == true && isHeroTexPointDownCrossing == true)
				HeroTitle.move(HeroSpeed, 0);
			else if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == false)
				isDrawindUnderLevel = true;
			else if (isHeroTexPointUpCrossing == false && isHeroTexPointDownCrossing == true)
				isDrawindUnderLevel = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
		{
			HeroTitle.move(HeroSpeed, 0);
			isStay = false;
		
			checkCrossing(allRoom, "Right");

			if (isHeroTexPointUpCrossing == true && isHeroTexPointMiddleCrossing == true && isHeroTexPointDownCrossing == true)
				HeroTitle.move(-HeroSpeed, 0);
			else if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == false)
				isDrawindUnderLevel = true;
			else if (isHeroTexPointUpCrossing == false && isHeroTexPointDownCrossing == true)
				isDrawindUnderLevel = false;
		}

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
		{
			HeroTitle.move(0, -HeroSpeed);
			isStay = false;
			checkCrossing(allRoom, "Up");

			if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == true)
				HeroTitle.move(0, HeroSpeed);
			else if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == false)
				isDrawindUnderLevel = true;
		}



		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
		{
			HeroTitle.move(0, HeroSpeed);
			isStay = false;
			checkCrossing(allRoom, "Down");

			if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == true)
				HeroTitle.move(0, -HeroSpeed);
			else if (isHeroTexPointUpCrossing == false && isHeroTexPointDownCrossing == true)
				isDrawindUnderLevel = false;
		}

		setHeroAnimation();
		
	}
	
	if (isTeleporting == true)
	{
		if (teleportTimer <= 20 )
		{
			if (teleportDirection == "Up")
			{
				HeroTitle.move(0, -3);
				checkCrossing(allRoom, teleportDirection);

				if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == true)
					HeroTitle.move(0, 3);
				else if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == false)
					isDrawindUnderLevel = true;
			}
			if (teleportDirection == "Down")
			{
				HeroTitle.move(0, 3);
				checkCrossing(allRoom, teleportDirection);

				if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == true)
					HeroTitle.move(0, -3);
				else if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == false)
					isDrawindUnderLevel = true;
			}
			if (teleportDirection == "Left")
			{
				HeroTitle.move(-3, 0);
				checkCrossing(allRoom, teleportDirection);

				if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == true)
					HeroTitle.move(3, 0);
				else if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == false)
					isDrawindUnderLevel = true;
			}
			if (teleportDirection == "Right")
			{
				HeroTitle.move(3, 0);
				checkCrossing(allRoom, teleportDirection);

				if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == true)
					HeroTitle.move(-3, 0);
				else if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == false)
					isDrawindUnderLevel = true;
			}
			if (teleportDirection == "RightUp")
			{
				HeroTitle.move(3, -3);
				checkCrossing(allRoom, "Right");

				if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == true)
					HeroTitle.move(-3, 0);
				else if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == false)
					isDrawindUnderLevel = true;

				checkCrossing(allRoom, "Up");

				if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == true)
					HeroTitle.move(0, 3);
				else if (isHeroTexPointUpCrossing == true && isHeroTexPointDownCrossing == false)
					isDrawindUnderLevel = true;
			}
			teleportTimer++;
		}
		else
		{
			teleportTimer = 0;
			isTeleporting = false;
		}
	}
	/*HeroGun.setPosition(HeroTitle.getPosition());

	float rad = atan2(window.mapPixelToCoords(sf::Mouse::getPosition(window)).x - HeroTitle.getPosition().x, window.mapPixelToCoords(sf::Mouse::getPosition(window)).y - HeroTitle.getPosition().y);
	float degree = rad / 3.1415926 * 180;
	HeroGun.setRotation(-degree + 90);*/

}




void Hero::collision(std::vector<Enemy*>& enemy, std::vector<Bullet>& bullet)
{
	shootingTimer++;
	if (isInvincible == true)
	{
		invincibleTimer++;
		for (int i = 0; i < bullet.size(); i++)
		{
			if (HeroTitle.getGlobalBounds().intersects(bullet[i].bulletTitle.getGlobalBounds()) && bullet[i].isHero == false)
				bullet.erase(bullet.begin() + i);
		}
		if (invincibleTimer >= 60)
		{
			isInvincible = false;
			//HeroTitle.setColor(sf::Color::White);
			invincibleTimer = 0;
			
		}

	}
	else 
	{
		for (int i = 0; i < enemy.size(); i++)
		{

			if (HeroTitle.getGlobalBounds().intersects(enemy[i]->enemyTitle.getGlobalBounds()))
			{
				health--; isInvincible = true;
				//HeroTitle.setColor(sf::Color::Red);
				if (enemy[i]->isDieCollision == true)
					enemy.erase(enemy.begin() + i);

			}

		}
		for (int i = 0; i < bullet.size(); i++)
		{

			if (HeroTitle.getGlobalBounds().intersects(bullet[i].bulletTitle.getGlobalBounds()) && bullet[i].isHero == false)
			{
				
					health--; isInvincible = true;
					//HeroTitle.setColor(sf::Color::Red);
					bullet.erase(bullet.begin() + i);
				
			}

		}
	}
}

void Hero::updateMouseDirection(sf::RenderWindow& window)
{
	sf::Mouse mouse;
	sf::Vector2f directionbuf = HeroTitle.getPosition() - window.mapPixelToCoords(mouse.getPosition(window));

	if (directionbuf.x <= 0 && abs(directionbuf.x) > 2 * abs(directionbuf.y))
		mouseDirection = "Right";
		
	else if (directionbuf.x <= 0 && abs(directionbuf.x) < 2 * abs(directionbuf.y) && directionbuf.y > 0 && abs(directionbuf.x) > 0.5 * abs(directionbuf.y))
		mouseDirection = "RightUp";

	else if (directionbuf.x <= 0 && abs(directionbuf.x) < 2 * abs(directionbuf.y) && directionbuf.y < 0 && abs(directionbuf.x) > 0.5 * abs(directionbuf.y))
		mouseDirection = "RightDown";
		
	else if (directionbuf.x > 0 && abs(directionbuf.x) > 2 * abs(directionbuf.y))
		mouseDirection = "Left";

	else if (directionbuf.x > 0 && abs(directionbuf.x) < 2 * abs(directionbuf.y) && directionbuf.y > 0 && abs(directionbuf.x) > 0.5 * abs(directionbuf.y))
		mouseDirection = "LeftUp";
	
	else if (directionbuf.x > 0 && abs(directionbuf.x) < 2 * abs(directionbuf.y) && directionbuf.y < 0 && abs(directionbuf.x) > 0.5 * abs(directionbuf.y))
		mouseDirection = "LeftDown";
		
	else if (directionbuf.y <= 0 && abs(directionbuf.x) <   2 * abs(directionbuf.y))
		mouseDirection = "Down";
	
	else if (directionbuf.y >= 0 && abs(directionbuf.x) < 2 *  abs(directionbuf.y))
		mouseDirection = "Up";
}

void Hero::setHeroAnimation()
{
	if (mouseDirection == "Up")
	{
		if (isStay == false)
		{
			HeroAnimationBackWalk.update(HeroTitle, 8);
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(1, 1);
		}
		else
		{
			HeroAnimationBackStay.update(HeroTitle, 4, 5, "MY COCK IS MUCH BIGGER THAN YOURS!!!");
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(1, 1);
		}
	}
	if (mouseDirection == "Down")
	{
		if (isStay == false)
		{
			HeroAnimationFrontWalk.update(HeroTitle, 8);
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(1, 1);
		}
		else
		{
			HeroAnimationFrontStay.update(HeroTitle, 4, 5, "MY COCK IS MUCH BIGGER THAN YOURS!!!");
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(1, 1);
		}

	}
	if (mouseDirection == "Left")
	{
		if (isStay == false)
		{
			HeroAnimationRightWalk.update(HeroTitle, 8);
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(-1, 1);
		}
		else
		{
			HeroAnimationRightStay.update(HeroTitle, 4, 5, "MY COCK IS MUCH BIGGER THAN YOURS!!!");
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(-1, 1);
		}
	}
	if (mouseDirection == "Right")
	{
		if (isStay == false)
		{
			HeroAnimationRightWalk.update(HeroTitle, 8);
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(1, 1);
		}
		else
		{
			HeroAnimationRightStay.update(HeroTitle, 4, 5, "MY COCK IS MUCH BIGGER THAN YOURS!!!");
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(1, 1);
		}
	}

	if (mouseDirection == "RightUp")
	{
		if (isStay == false)
		{
			HeroAnimationRightUpWalk.update(HeroTitle, 8);
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(1, 1);
		}
		else
		{
			HeroAnimationRightUpStay.update(HeroTitle, 4, 5, "MY COCK IS MUCH BIGGER THAN YOURS!!!");
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(1, 1);
		}
	}
	if (mouseDirection == "LeftUp")
	{
		if (isStay == false)
		{
			HeroAnimationRightUpWalk.update(HeroTitle, 8);
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(-1, 1);
		}
		else
		{
			HeroAnimationRightUpStay.update(HeroTitle, 4, 5, "MY COCK IS MUCH BIGGER THAN YOURS!!!");
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(-1, 1);
		}
	}
	if (mouseDirection == "RightDown")
	{
		if (isStay == false)
		{
			HeroAnimationRightDownWalk.update(HeroTitle, 8);
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(1, 1);
		}
		else
		{
			HeroAnimationRightDownStay.update(HeroTitle, 4, 5, "MY COCK IS MUCH BIGGER THAN YOURS!!!");
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(1, 1);
		}
	}
	if (mouseDirection == "LeftDown")
	{
		if (isStay == false)
		{
			HeroAnimationRightDownWalk.update(HeroTitle, 8);
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(-1, 1);
		}
		else
		{
			HeroAnimationRightDownStay.update(HeroTitle, 4, 5, "MY COCK IS MUCH BIGGER THAN YOURS!!!");
			HeroTitle.setOrigin(HeroTitle.getGlobalBounds().width / 2, HeroTitle.getGlobalBounds().height / 2);
			HeroTitle.setScale(-1, 1);
		}
	}
}

void Hero::shoot(sf::RenderWindow& window, std::vector<Bullet>& bullet)
{
	if (shootingTimer > 30)
	{
		Bullet bulletBuf;


		bulletBuf.bulletTitle.setPosition(HeroTitle.getPosition());
		bulletBuf.direction = window.mapPixelToCoords(sf::Mouse::getPosition(window)) - HeroTitle.getPosition();
		float length = sqrt(pow(bulletBuf.direction.x, 2) + pow(bulletBuf.direction.y, 2));
		bulletBuf.direction.x /= length;
		bulletBuf.direction.y /= length;
		bulletBuf.speed = 5;
		bulletBuf.isHero = true;
		bullet.push_back(bulletBuf);
		shootingTimer = 0;
	}
}

void Hero::draw(sf::RenderWindow& window)
{
	window.draw(HeroTitle);
	//window.draw(HeroGun);
}

void Hero::checkCrossing(std::vector <Room>& allRoom, std::string direction)
{
	isHeroTexPointUpCrossing = false;
	isHeroTexPointMiddleCrossing = false;
	isHeroTexPointDownCrossing = false;

	if (direction == "Left")
	{
		HeroTexPointUp = { HeroTitle.getPosition().x - HeroTitle.getGlobalBounds().width / 2, HeroTitle.getPosition().y - HeroTitle.getGlobalBounds().height / 4 };
		HeroTexPointMiddle = { HeroTitle.getPosition().x - HeroTitle.getGlobalBounds().width / 2, HeroTitle.getPosition().y };
		HeroTexPointDown = { HeroTitle.getPosition().x - HeroTitle.getGlobalBounds().width / 2, HeroTitle.getPosition().y + HeroTitle.getGlobalBounds().height / 4 };
	}
	if (direction == "Right")
	{
		HeroTexPointUp = { HeroTitle.getPosition().x + HeroTitle.getGlobalBounds().width / 2, HeroTitle.getPosition().y - HeroTitle.getGlobalBounds().height / 4 };
		HeroTexPointMiddle = { HeroTitle.getPosition().x + HeroTitle.getGlobalBounds().width / 2, HeroTitle.getPosition().y };
		HeroTexPointDown = { HeroTitle.getPosition().x + HeroTitle.getGlobalBounds().width / 2, HeroTitle.getPosition().y + HeroTitle.getGlobalBounds().height / 4 };
	}
	if (direction == "Up")
	{
		HeroTexPointUp = { HeroTitle.getPosition().x, HeroTitle.getPosition().y - HeroTitle.getGlobalBounds().height / 2 };
		HeroTexPointDown = { HeroTitle.getPosition().x, HeroTitle.getPosition().y + HeroTitle.getGlobalBounds().height / 4 };
	}
	if (direction == "Down")
	{
		HeroTexPointUp = { HeroTitle.getPosition().x, HeroTitle.getPosition().y - HeroTitle.getGlobalBounds().height / 4 };
		HeroTexPointDown = { HeroTitle.getPosition().x, HeroTitle.getPosition().y + HeroTitle.getGlobalBounds().height / 2 };
	}

		for (int i = 0; i < allRoom.size(); i++)
		{
			for (int j = 0; j < allRoom[i].wallTitle.size(); j++)
			{
				if (allRoom[i].wallTitle[j].getGlobalBounds().contains(HeroTexPointUp))
					isHeroTexPointUpCrossing = true;
				if (allRoom[i].wallTitle[j].getGlobalBounds().contains(HeroTexPointMiddle))
					isHeroTexPointMiddleCrossing = true;
				if (allRoom[i].wallTitle[j].getGlobalBounds().contains(HeroTexPointDown))
					isHeroTexPointDownCrossing = true;
			}
		}
	
}

