#include <SFML/Graphics.hpp>
#include"Room.h"
#include"MapGenerator.h"



int maina()
{
	sf::RenderWindow window(sf::VideoMode(1200, 900), "MapTest");
	window.setFramerateLimit(60);
	sf::View view(sf::FloatRect(4000, 4000, 1200, 900));
	srand(time(0));
		
	int** allField = new int*[200];
	for (int i = 0; i<200; i++) 
	{
		allField[i] = new int[200];
		for (int j = 0; j<200; j++) 
		{
			allField[i][j] = 5;
		}
	}
		
	
		MapGenerator mapGen(allField);
	
		

		
	
	while (window.isOpen())
	{
		sf::Event event;
		while (window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed)
				window.close();
		
		}
		
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::A))
			view.move(-30, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::D))
			view.move(30, 0);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::W))
			view.move(0, -30);
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
			view.move(0, 30);


		window.clear();
		
		window.setView(view);
		for (int i = 0; i < 200; i++)
		{
			for (int j = 0; j < 200; j++)
			{
				if (allField[i][j] == 2)
				{
					sf::RectangleShape wallTitle;
					wallTitle.setSize({ 64, 64 });
					wallTitle.setPosition(j * 64, i * 64);
					window.draw(wallTitle);

				}
				
			}
		}
			
		
		window.display();
	}

	return 0;
}
