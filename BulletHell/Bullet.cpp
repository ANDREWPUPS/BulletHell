#include "Bullet.h"
#include<vector>


Bullet::Bullet()
{
	bulletTitle.setRadius(2.5);

}
int Bullet::move(std::vector<sf::Sprite>& wallTitle)
{
	for (int i = 0; i < wallTitle.size(); i++)
	{
		if (bulletTitle.getGlobalBounds().intersects(wallTitle[i].getGlobalBounds()))
			return 0;
	}
		bulletTitle.move(direction.x * speed, direction.y * speed);
		return 1;


}