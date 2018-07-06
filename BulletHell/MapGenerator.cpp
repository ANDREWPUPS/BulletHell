#include "MapGenerator.h"
#include <iostream>
MapGenerator::MapGenerator(int** allField)
{
	for (int i = 0; i < 6; i++)
		loadedRooms.push_back(Room (i));

	generatingMap(allField);
}


void MapGenerator::generatingMap(int** allField)
{
	loadedRooms[0].positionAllField.first = 100;
	loadedRooms[0].positionAllField.second = 100;
	for (int i = 0; i < loadedRooms[0].doors.size(); i++)
	{
		loadedRooms[0].doors[i].positionAllField.first = 100;
		loadedRooms[0].doors[i].positionAllField.second = 100;
		allOpenDoors.push_back(loadedRooms[0].doors[i]);
	}
	loadedRooms[0].isClear = true;
	allGeneratedRooms.push_back(loadedRooms[0]);
	
	std::vector<Room::door>::iterator find;
	int number_of_door;
	int allChecks = 0;
	int check_collision = 0;
	int nextRoom = 0;
	std::vector<int> checkedRooms;
	std::pair<int, int> position_next_door_allField;
	std::string direction_of_next_door;

	for (int k = 0; k < 10; k++)
	{
		do
		{
			number_of_door = rand() % allOpenDoors.size();


			if (allOpenDoors[number_of_door].direction == "up")
			{
				direction_of_next_door = "down";
				position_next_door_allField.first = allOpenDoors[number_of_door].positionAllField.first + allOpenDoors[number_of_door].position / loadedRooms[allOpenDoors[number_of_door].number].xSize - 1;
				position_next_door_allField.second = allOpenDoors[number_of_door].positionAllField.second + allOpenDoors[number_of_door].position % loadedRooms[allOpenDoors[number_of_door].number].xSize;
			}

			if (allOpenDoors[number_of_door].direction == "down")
			{
				direction_of_next_door = "up";
				position_next_door_allField.first = allOpenDoors[number_of_door].positionAllField.first + allOpenDoors[number_of_door].position / loadedRooms[allOpenDoors[number_of_door].number].xSize + 1;
				position_next_door_allField.second = allOpenDoors[number_of_door].positionAllField.second + allOpenDoors[number_of_door].position % loadedRooms[allOpenDoors[number_of_door].number].xSize;
			}

			if (allOpenDoors[number_of_door].direction == "left")
			{
				direction_of_next_door = "right";
				position_next_door_allField.first = allOpenDoors[number_of_door].positionAllField.first + allOpenDoors[number_of_door].position / loadedRooms[allOpenDoors[number_of_door].number].xSize;
				position_next_door_allField.second = allOpenDoors[number_of_door].positionAllField.second + allOpenDoors[number_of_door].position % loadedRooms[allOpenDoors[number_of_door].number].xSize - 1;
			}

			if (allOpenDoors[number_of_door].direction == "right")
			{
				direction_of_next_door = "left";
				position_next_door_allField.first = allOpenDoors[number_of_door].positionAllField.first + allOpenDoors[number_of_door].position / loadedRooms[allOpenDoors[number_of_door].number].xSize;
				position_next_door_allField.second = allOpenDoors[number_of_door].positionAllField.second + allOpenDoors[number_of_door].position % loadedRooms[allOpenDoors[number_of_door].number].xSize + 1;
			}

			allChecks = 0;
			check_collision = 0;
			nextRoom = 0;
			checkedRooms.push_back(0);
			while (allChecks != loadedRooms.size())
			{
				nextRoom = rand() % (loadedRooms.size() - 1) + 1;
				
				checkedRooms.push_back(nextRoom);
				find = std::find_if(loadedRooms[nextRoom].doors.begin(), loadedRooms[nextRoom].doors.end(), [&direction_of_next_door](Room::door d){return d.direction == direction_of_next_door; });
				loadedRooms[nextRoom].positionAllField.first = position_next_door_allField.first - loadedRooms[nextRoom].doors[find - loadedRooms[nextRoom].doors.begin()].position / loadedRooms[nextRoom].xSize;
				loadedRooms[nextRoom].positionAllField.second = position_next_door_allField.second - loadedRooms[nextRoom].doors[find - loadedRooms[nextRoom].doors.begin()].position % loadedRooms[nextRoom].xSize;

				check_collision = checkCollision(loadedRooms[nextRoom], allField);
				if (check_collision == 1)
					break;
				allChecks++;
			}
			checkedRooms.clear();
		} while (allChecks == loadedRooms.size());
		
		Room::door buf;
		buf = allOpenDoors[number_of_door];
		allField[allOpenDoors[number_of_door].positionAllField.first + allOpenDoors[number_of_door].position / loadedRooms[allOpenDoors[number_of_door].number].xSize][allOpenDoors[number_of_door].positionAllField.second + allOpenDoors[number_of_door].position % loadedRooms[allOpenDoors[number_of_door].number].xSize] = 4;
		allOpenDoors.erase(allOpenDoors.begin() + number_of_door);
		for (int i = 0; i < loadedRooms[nextRoom].ySize; i++)
		{
			for (int j = 0; j < loadedRooms[nextRoom].xSize; j++)
			{
				allField[loadedRooms[nextRoom].positionAllField.first + i][loadedRooms[nextRoom].positionAllField.second + j] = loadedRooms[nextRoom].field[i * loadedRooms[nextRoom].xSize + j];
			}
		}

		for (int i = 0; i < loadedRooms[nextRoom].doors.size(); i++)
		{
			if (i != find - loadedRooms[nextRoom].doors.begin())
			{
				loadedRooms[nextRoom].doors[i].positionAllField.first = loadedRooms[nextRoom].positionAllField.first;
				loadedRooms[nextRoom].doors[i].positionAllField.second = loadedRooms[nextRoom].positionAllField.second;
				allOpenDoors.push_back(loadedRooms[nextRoom].doors[i]);
			}
			else
			{
				loadedRooms[nextRoom].doors[i].positionAllField.first = loadedRooms[nextRoom].positionAllField.first;
				loadedRooms[nextRoom].doors[i].positionAllField.second = loadedRooms[nextRoom].positionAllField.second;
			}

		}
		allGeneratedRooms.push_back(loadedRooms[nextRoom]);
	}
	
	for (int i = 0; i < allGeneratedRooms.size(); i++)
	{
		for (int j = 0; j < allGeneratedRooms[i].doors.size(); j++)
		{
			allGeneratedRooms[i].doors[j].number_in_allGeneratedRooms = i;
		}
	}
	
	
	for (int i = 0; i < allOpenDoors.size(); i++)
	{
		allField[allOpenDoors[i].positionAllField.first + allOpenDoors[i].position / loadedRooms[allOpenDoors[i].number].xSize][allOpenDoors[i].positionAllField.second + allOpenDoors[i].position % loadedRooms[allOpenDoors[i].number].xSize] = 2;
		for (int j = 0; j < allGeneratedRooms.size(); j++)
		{
			for (int z = 0; z < allGeneratedRooms[j].doors.size(); z++)
			{
				if (allGeneratedRooms[j].doors[z] == allOpenDoors[i])
				{
					allGeneratedRooms[j].doors[z].isUsing = false;
					if (allGeneratedRooms[j].doors[z].direction == "up")
					{
						allGeneratedRooms[j].field[allGeneratedRooms[j].doors[z].position + allGeneratedRooms[j].xSize] = 2;
						allGeneratedRooms[j].field[allGeneratedRooms[j].doors[z].position + allGeneratedRooms[j].xSize * 2] = 1;
					}
					if (allGeneratedRooms[j].doors[z].direction == "left")
					{
						allGeneratedRooms[j].field[allGeneratedRooms[j].doors[z].position - allGeneratedRooms[j].xSize] = 3;
						allGeneratedRooms[j].field[allGeneratedRooms[j].doors[z].position - allGeneratedRooms[j].xSize * 2] = 3;
					}
					if (allGeneratedRooms[j].doors[z].direction == "right")
					{
						allGeneratedRooms[j].field[allGeneratedRooms[j].doors[z].position - allGeneratedRooms[j].xSize] = 3;
						allGeneratedRooms[j].field[allGeneratedRooms[j].doors[z].position - allGeneratedRooms[j].xSize * 2] = 3;
					}
					if (allGeneratedRooms[j].doors[z].direction == "down")
					{
						
						for (int b = (allGeneratedRooms[j].ySize - 3) * allGeneratedRooms[j].xSize; b < (allGeneratedRooms[j].ySize - 2) * allGeneratedRooms[j].xSize; b++)
						{
							allGeneratedRooms[j].field[b] = 3;																																																
						}
						for (int b = (allGeneratedRooms[j].ySize - 2) * allGeneratedRooms[j].xSize; b < (allGeneratedRooms[j].ySize - 1) * allGeneratedRooms[j].xSize; b++)
						{
							allGeneratedRooms[j].field[b] = 2;
						}
						for (int b = (allGeneratedRooms[j].ySize - 1) * allGeneratedRooms[j].xSize; b < (allGeneratedRooms[j].ySize - 0) * allGeneratedRooms[j].xSize; b++)
						{
							allGeneratedRooms[j].field[b] = 1;
						}
						
					}
				}
			}
		}
	}

	for (int i = 0; i < allGeneratedRooms.size(); i++)
	{
		for (int j = 0; j < allGeneratedRooms[i].doors.size(); j++)
		{
			if (allGeneratedRooms[i].doors[j].isUsing == true)
			{
				if (allGeneratedRooms[i].doors[j].nearDoor == 0)
				{
					std::pair<int, int> position_all_field_near_door;
					if (allGeneratedRooms[i].doors[j].direction == "up")
					{
						position_all_field_near_door.first = allGeneratedRooms[i].positionAllField.first + allGeneratedRooms[i].doors[j].position / allGeneratedRooms[i].xSize - 1;
						position_all_field_near_door.second = allGeneratedRooms[i].positionAllField.second + allGeneratedRooms[i].doors[j].position % allGeneratedRooms[i].xSize;
					}
					else if (allGeneratedRooms[i].doors[j].direction == "down")
					{
						position_all_field_near_door.first = allGeneratedRooms[i].positionAllField.first + allGeneratedRooms[i].doors[j].position / allGeneratedRooms[i].xSize + 1;
						position_all_field_near_door.second = allGeneratedRooms[i].positionAllField.second + allGeneratedRooms[i].doors[j].position % allGeneratedRooms[i].xSize;
					}
					else if (allGeneratedRooms[i].doors[j].direction == "left")
					{
						position_all_field_near_door.first = allGeneratedRooms[i].positionAllField.first + allGeneratedRooms[i].doors[j].position / allGeneratedRooms[i].xSize;
						position_all_field_near_door.second = allGeneratedRooms[i].positionAllField.second + allGeneratedRooms[i].doors[j].position % allGeneratedRooms[i].xSize - 1;
					}
					else if (allGeneratedRooms[i].doors[j].direction == "right")
					{
						position_all_field_near_door.first = allGeneratedRooms[i].positionAllField.first + allGeneratedRooms[i].doors[j].position / allGeneratedRooms[i].xSize;
						position_all_field_near_door.second = allGeneratedRooms[i].positionAllField.second + allGeneratedRooms[i].doors[j].position % allGeneratedRooms[i].xSize + 1;
					}
					
					for (int z = 0; z < allGeneratedRooms.size(); z++)
					{
						if (z != i)
						{
							for (int u = 0; u < allGeneratedRooms[z].doors.size(); u++)
							{
								std::pair<int, int> position_all_field_door;
								position_all_field_door.first = allGeneratedRooms[z].positionAllField.first + allGeneratedRooms[z].doors[u].position / allGeneratedRooms[z].xSize;
								position_all_field_door.second = allGeneratedRooms[z].positionAllField.second + allGeneratedRooms[z].doors[u].position % allGeneratedRooms[z].xSize;
								if (position_all_field_door == position_all_field_near_door)
								allGeneratedRooms[i].doors[j].nearDoor = &allGeneratedRooms[z].doors[u];
							}
						}
					}
				}
			}
		}

		for (int v = 0; v < allGeneratedRooms[i].field.size(); v++)
		{
			if (allGeneratedRooms[i].field[v] == 1 || allGeneratedRooms[i].field[v] == 2 || allGeneratedRooms[i].field[v] == 3)
				walls.push_back((allGeneratedRooms[i].positionAllField.first + v / allGeneratedRooms[i].xSize) * 200 + (allGeneratedRooms[i].positionAllField.second + v % allGeneratedRooms[i].xSize));
		}
	}
	
	
	
}

int MapGenerator::checkCollision(Room room, int** allField)
{
	for (int i = 0; i < room.ySize; i++)
	{
		for (int j = 0; j < room.xSize; j++)
		{
			if (allField[room.positionAllField.first + i][room.positionAllField.second + j] != 5)
				return 0;
		}
	}
	return 1;
}

