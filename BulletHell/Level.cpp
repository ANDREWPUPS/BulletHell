#include "Level.h"
#include "Hero.h"

Level::Level(std::vector<Room>& allGeneratedRoomsFromMapGenerator)
{
	allGeneratedRooms = allGeneratedRoomsFromMapGenerator;
	allGeneratedRooms[0].isClear = true;
	downtex.loadFromFile("Resourses/Sprites/title_down.png");
	midletex.loadFromFile("Resourses/Sprites/title_midle.png");
	uptex.loadFromFile("Resourses/Sprites/title_up.png");
	doortex.loadFromFile("Resourses/Sprites/door.png");
}

int Level::HeroCurrentRoom(Hero& hero)
{
	for (int i = 0; i < allGeneratedRooms.size(); i++)
	{
		if ((int)hero.HeroTitle.getPosition().y / 64 > allGeneratedRooms[i].positionAllField.first && (int)hero.HeroTitle.getPosition().y / 64 < allGeneratedRooms[i].positionAllField.first + allGeneratedRooms[i].ySize)
		{
			if ((int)hero.HeroTitle.getPosition().x / 64 > allGeneratedRooms[i].positionAllField.second && (int)hero.HeroTitle.getPosition().x / 64 < allGeneratedRooms[i].positionAllField.second + allGeneratedRooms[i].xSize)
				return i;
		}
	}
}
void Level::spawnEnemy_and_update(Hero& hero, std::vector<int>& allWall, int** allField)
{

	for (int i = 0; i < allGeneratedRooms.size(); i++)
	{
		if (hero.HeroTitle.getPosition().y / 64 > allGeneratedRooms[i].positionAllField.first && hero.HeroTitle.getPosition().y / 64 < allGeneratedRooms[i].positionAllField.first + allGeneratedRooms[i].ySize)
		{
			if (hero.HeroTitle.getPosition().x / 64 > allGeneratedRooms[i].positionAllField.second && hero.HeroTitle.getPosition().x / 64 < allGeneratedRooms[i].positionAllField.second + allGeneratedRooms[i].xSize)
				heroCurrentRoom = i;
		}
	} 
	if (allGeneratedRooms[heroCurrentRoom].isClear == false && allGeneratedRooms[heroCurrentRoom].isCombat == false)
	{
		if (allGeneratedRooms[heroCurrentRoom].Waves != 0 && allField[(int)(hero.HeroTitle.getPosition().y + hero.HeroTitle.getGlobalBounds().height) / 64][(int)hero.HeroTitle.getPosition().x / 64] != 4 && allField[(int)(hero.HeroTitle.getPosition().y - hero.HeroTitle.getGlobalBounds().height) / 64][(int)hero.HeroTitle.getPosition().x / 64] != 4 && allField[(int)(hero.HeroTitle.getPosition().y) / 64][(int)(hero.HeroTitle.getPosition().x + hero.HeroTitle.getGlobalBounds().height) / 64] != 4 && allField[(int)(hero.HeroTitle.getPosition().y) / 64][(int)(hero.HeroTitle.getPosition().x - hero.HeroTitle.getGlobalBounds().height) / 64] != 4)
		{
			allGeneratedRooms[heroCurrentRoom].isCombat = true;
			allGeneratedRooms[heroCurrentRoom].spawn(allWall);
			allGeneratedRooms[heroCurrentRoom].Waves--;
			allGeneratedRooms[heroCurrentRoom].updateDoors(downtex, midletex, uptex, doortex);
		}
	}

	update(allWall);
}
void Level::update(std::vector<int>& allWall)
{
	if (allGeneratedRooms[heroCurrentRoom].isCombat == true)
		allGeneratedRooms[heroCurrentRoom].update();
	if (allGeneratedRooms[heroCurrentRoom].isCombat == true && allGeneratedRooms[heroCurrentRoom].enemies.size() == 0 && allGeneratedRooms[heroCurrentRoom].spawner.active == false && allGeneratedRooms[heroCurrentRoom].Waves != 0)
	{
		allGeneratedRooms[heroCurrentRoom].Waves--;
		allGeneratedRooms[heroCurrentRoom].spawn(allWall);
	}
	if (allGeneratedRooms[heroCurrentRoom].isCombat == true && allGeneratedRooms[heroCurrentRoom].enemies.size() == 0 && allGeneratedRooms[heroCurrentRoom].spawner.active == false)
	{
		allGeneratedRooms[heroCurrentRoom].isCombat = false;
		allGeneratedRooms[heroCurrentRoom].isClear = true;
	}
	allGeneratedRooms[heroCurrentRoom].updateDoors(downtex, midletex, uptex, doortex);
}

void Level::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < allGeneratedRooms.size(); i++)
	{
		if (allGeneratedRooms[i].isClear == true || allGeneratedRooms[i].isCombat == true)
			allGeneratedRooms[i].draw(window);
	}
}

