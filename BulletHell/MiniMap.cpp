#include "MiniMap.h"

MiniMap::MiniMap()
{
	font.loadFromFile("Resourses/font.otf");
	marker.setFont(font);
	sf::Vector2f mousePosOld = { 0, 0 };
}
void MiniMap::draw(Level& level, Hero& hero, sf::RenderWindow& window)
{
	blackShape.setFillColor(sf::Color(0, 0, 0, 240));
	blackShape.setSize(sf::Vector2f(100000, 100000));
	blackShape.setOrigin(blackShape.getGlobalBounds().width / 2, blackShape.getGlobalBounds().height / 2);
	blackShape.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2)));

	window.draw(blackShape);
	level.draw(window);
	for (int i = 0; i < level.allGeneratedRooms.size(); i++)
	{
		if (level.allGeneratedRooms[i].isClear == true)
		{
			for (int j = 0; j < level.allGeneratedRooms[i].doors.size(); j++)
			{
				if (level.allGeneratedRooms[i].doors[j].isUsing == true)
				{
					if (level.allGeneratedRooms[level.allGeneratedRooms[i].doors[j].nearDoor->number_in_allGeneratedRooms].isClear == false)
					{
						sf::RectangleShape buf;
						buf.setSize({ 64, 64 });
						buf.setPosition(64 * (level.allGeneratedRooms[i].positionAllField.second + level.allGeneratedRooms[i].doors[j].position % level.allGeneratedRooms[i].xSize), 64 * (level.allGeneratedRooms[i].positionAllField.first + level.allGeneratedRooms[i].doors[j].position / level.allGeneratedRooms[i].xSize));
						buf.setFillColor(sf::Color::Green);
						window.draw(buf);
					}
				}
			}
		}
	}
	hero.draw(window);
}

void MiniMap::update(sf::RenderWindow& window, sf::View& minimapview)
{
	if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
	{
		sf::Mouse mouse;
		sf::Vector2f mousePosNew;
		if (mousePosOld.x == 0 && mousePosOld.y == 0)
			mousePosOld = window.mapPixelToCoords(sf::Vector2i(mouse.getPosition(window)));

		mousePosNew = window.mapPixelToCoords(sf::Vector2i(mouse.getPosition(window)));
		if (mousePosNew != mousePosOld)
		{
			sf::Vector2f direction;
			direction = mousePosNew - mousePosOld;
			minimapview.move(-direction);

		}
		mousePosOld = mousePosNew;
	}
	else mousePosOld = { 0, 0 };
}

