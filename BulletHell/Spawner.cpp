#include "Spawner.h"
#include "Room.h"
#include "enemyPurple.h"
#include "enemySuicide.h"

Spawner::Spawner(){}
Spawner::Spawner(Room& heroCurrentRoom, std::vector<int>& allWall)
{
	spawnerAnimation = Animation("Resourses/Sprites/FireSpawner.png");
	int enemiesSum = rand() % (heroCurrentRoom.maxEnemies - heroCurrentRoom.minEnemies + 1) + heroCurrentRoom.minEnemies;
	float bufx = heroCurrentRoom.positionAllField.second;
	float bufy = heroCurrentRoom.positionAllField.first;
	std::vector<int> enemypos_for_checking;
	for (int i = 0; i < enemiesSum; i++)
	{
		int type = rand() % 2;
		Enemy* buf = 0;
		if (type == 0) {
			buf = new enemyPurple();
		}
		else if (type == 1) {
			buf = new enemySuicide();
		}
		bufx = rand() % (heroCurrentRoom.xSize) + heroCurrentRoom.positionAllField.second;
		bufy = rand() % (heroCurrentRoom.ySize) + heroCurrentRoom.positionAllField.first;
		while (heroCurrentRoom.field[(bufy - heroCurrentRoom.positionAllField.first) * heroCurrentRoom.xSize + bufx - heroCurrentRoom.positionAllField.second] != 0 || std::find(enemypos_for_checking.begin(), enemypos_for_checking.end(), bufx + bufy * 200) != enemypos_for_checking.end())
		{
			bufx = rand() % (heroCurrentRoom.xSize) + heroCurrentRoom.positionAllField.second;
			bufy = rand() % (heroCurrentRoom.ySize) + heroCurrentRoom.positionAllField.first;
		}
		
		buf->setPosition({ bufx * 64 + 32, bufy * 64 + 32});
		enemypos_for_checking.push_back(bufx + bufy * 200);
		enemies.push_back(buf);
			
	}
}

void Spawner::update(std::vector<Enemy*>& enemiesFromRoom) 
{
	spawnerAnimation.update(spawnerSprite, 4);
	if (active && timer.getElapsedTime().asSeconds() > 2) 
	{
		for (int i = 0; i < enemies.size(); i++)
		{
			enemiesFromRoom.push_back(enemies[i]);
		}
			active = false;
		}
	
}

void Spawner::draw(sf::RenderWindow& window) {
	if (!active) return;
	for (int i = 0; i < enemies.size(); i++)
	{
		spawnerSprite.setOrigin(spawnerSprite.getGlobalBounds().width / 2, spawnerSprite.getGlobalBounds().height / 2);
		spawnerSprite.setPosition(enemies[i]->enemyTitle.getPosition());
		window.draw(spawnerSprite);
	}
	
}

