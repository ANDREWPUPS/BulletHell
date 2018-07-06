#pragma once
#include "Room.h"

class MapGenerator
{
public:
	std::vector<Room::door> allOpenDoors;
	std::vector<int> walls;
	MapGenerator(Room startRoom, int** allField);
	std::vector<Room> allGeneratedRooms;
	std::vector<Room> loadedRooms;

	MapGenerator(int** allField);

	void generatingMap(int** allField);
	
	void generatingMap(std::vector<Room>& allRoom, int** allField);

	int checkCollision(Room room, int** allField);
};