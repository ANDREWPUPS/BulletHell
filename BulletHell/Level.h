#pragma once
#include "Room.h"

class Level
{
public:
	std::vector<Room> allGeneratedRooms;
	int heroCurrentRoom = 0;
	sf::Texture downtex;
	sf::Texture midletex;
	sf::Texture uptex;;
	sf::Texture doortex;
	Level(std::vector<Room>& allGeneratedRoomsFromMapGenerator);

	void spawnEnemy_and_update(Hero& hero, std::vector<int>& allWall, int** allField);

	int HeroCurrentRoom(Hero& hero);
	
	void update(std::vector<int>& allWall);
	
	void draw(sf::RenderWindow& window);
	
};