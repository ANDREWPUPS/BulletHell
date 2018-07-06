#include"Room.h"
#include <fstream>
#include <iostream>
Room::Room(int n)
{
	std::ifstream mapFile("Resourses/Room/room" + std::to_string(n) + ".txt");
	
	std::string bla; 
	for (int i = 0; i<3; i++) {
		mapFile >> bla;
		if (bla == "maxEnemies") mapFile >> maxEnemies;
		else if (bla == "minEnemies") mapFile >> minEnemies;
		else if (bla == "waves") mapFile >> Waves;
	}
	std::string line;
	std::getline(mapFile, bla);
	while (std::getline(mapFile, line)) 
	{
		if (line != "")
		{
			for (int i = 0; i < line.size(); i++)
			{
				char c;
				c = line[i];
				if (c != ' ')
				{
					if (c == '^')
					{
						door bufDoor;
						bufDoor.position = field.size();
						bufDoor.direction = "up";
						bufDoor.number = n;
						doors.push_back(bufDoor);
						field.push_back(4);
					}
					else if (c == 'v')
					{
						door bufDoor;
						bufDoor.position = field.size();
						bufDoor.direction = "down";
						bufDoor.number = n;
						doors.push_back(bufDoor);
						field.push_back(4);
					}
					else if (c == '>')
					{
						door bufDoor;
						bufDoor.position = field.size();
						bufDoor.direction = "right";
						bufDoor.number = n;
						doors.push_back(bufDoor);
						field.push_back(4);
					}

					else if (c == '<')
					{
						door bufDoor;
						bufDoor.position = field.size();
						bufDoor.direction = "left";
						bufDoor.number = n;
						doors.push_back(bufDoor);
						field.push_back(4);
					}
					else
						field.push_back(c - '0');
				}
			}
		ySize++;
		}
	}
	xSize = field.size() / ySize;
}


void Room::updateDoors(sf::Texture &downtex, sf::Texture &midletex, sf::Texture &uptex, sf::Texture &doortex)
{
	wallTitle.clear();
	for (int i = 0; i < field.size(); i++)
	{
		sf::Sprite wallTitlebuf;
		wallTitlebuf.setPosition((positionAllField.second + i % xSize) * 64, (positionAllField.first + i / xSize) * 64);
		for (int j = 0; j < doors.size(); j++)
		{
			if (doors[j].position == i)
			{
				if (doors[j].isUsing == false)
				{
					wallTitlebuf.setTexture(uptex);
					wallTitle.push_back(wallTitlebuf);
				}

				if (isCombat == true && doors[j].isUsing == true)
				{
					wallTitlebuf.setTexture(doortex);
					wallTitle.push_back(wallTitlebuf);
				}
			}
		}

		if (field[i] == 1)
		{
			wallTitlebuf.setTexture(downtex);
			wallTitle.push_back(wallTitlebuf);
		}
		if (field[i] == 2)
		{
			wallTitlebuf.setTexture(midletex);
			wallTitle.push_back(wallTitlebuf);
		}
		if (field[i] == 3)
		{
			wallTitlebuf.setTexture(uptex);
			wallTitle.push_back(wallTitlebuf);
		}

	}
}
void Room::draw(sf::RenderWindow& window)
{
	for (int i = 0; i < wallTitle.size(); i++)
		window.draw(wallTitle[i]);
}
void Room::spawn(std::vector<int>& allWall)
{
	spawner = Spawner(*this, allWall);
}
void Room::update()
{
	spawner.update(enemies);
}