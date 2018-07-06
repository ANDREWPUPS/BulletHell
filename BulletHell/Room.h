#pragma once
#include<vector>
#include <SFML/Graphics.hpp>
#include"Spawner.h"
#include"Enemy.h"

class Room
{
public:
	std::vector <int> field;
	int xSize = 0;
	int ySize = 0;
	int maxEnemies = 0;
	int minEnemies = 0;
	int Waves = 0;
	bool isCombat = false;
	bool isClear = false;
	Spawner spawner;
	std::vector<Enemy*> enemies;
	struct door
	{
		int position;
		std::string direction;
		int number;
		std::pair<int, int> positionAllField;
		bool isUsing = true;
		door* nearDoor = 0;
		int number_in_allGeneratedRooms;

		bool operator==(door& other) { return position == other.position && positionAllField == other.positionAllField && number == other.number && isUsing == other.isUsing ; }
	};
	std::vector<door> doors;
	std::vector<int> wall;
	std::vector<sf::Sprite> wallTitle;
	std::pair<int, int> positionAllField;//позиция верхнего левого угла комнаты на общем поле

	Room(int n);//number of file

	void Room::updateDoors(sf::Texture &downtex, sf::Texture &midletex, sf::Texture &uptex, sf::Texture &doortex);

	void draw(sf::RenderWindow& window);
	
	void spawn(std::vector<int>& allWall);
	
	void update();
};