#include <SFML/Graphics.hpp>

#include"Enemy.h"
#include"FindWay.h"
#include"Hero.h"
#include"Room.h"
#include"Bullet.h"
#include"enemyPurple.h"
#include"enemySuicide.h"
#include"MapGenerator.h"
#include"Spawner.h"
#include"Level.h"
#include"MainMenu.h"
#include"GameMenu.h"
#include"EndMenu.h"
#include "MiniMap.h"
#include "Animation.h"

int handlePress(std::string& gameStage,  MainMenu& mainmenu, GameMenu& gamemenu, EndMenu& endmenu, sf::RenderWindow& window)
{
	if (gameStage == "MainMenu")
	{
		int menuBuf = mainmenu.update(window);
		if (menuBuf == 1)
			gameStage = "game";
		if (menuBuf == 0)
		{
			window.close();
			return 0;
		}
	}

	if (gameStage == "GameMenu")
	{
		int menuBuf = gamemenu.update(window);
		if (menuBuf == 1)
			gameStage = "game";
		if (menuBuf == 0)
		{
			window.close();
			return 0;
		}
		if (menuBuf == 2)
		{
			gameStage = "game";
			return 1;
		}
	}

	if (gameStage == "EndMenu")
	{
		int menuBuf = endmenu.update(window);
		if (menuBuf == 0)
		{
			window.close();
			return 0;
		}
		if (menuBuf == 2)
		{
			gameStage = "game";
			return 1;
		}
	}
}

int main()
{
	
	srand(time(0));
	sf::RenderWindow window(sf::VideoMode(1200, 800), "BulletHell");
	//sf::RenderWindow window(sf::VideoMode(1600, 900), "BulletHell");
	window.setVerticalSyncEnabled(true);
	const float scale = 0.5;
	window.setFramerateLimit(60);
	sf::Font font;
	font.loadFromFile("Resourses/font.otf");
	sf::Text healthText;
	std::string gameStage = "MainMenu";
	sf::Clock fps;
	MainMenu mainmenu(window);
	GameMenu gamemenu(window);
	EndMenu endmenu(window);
	MiniMap minimap;
	
	while (true)
	{
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
		Level level(mapGen.allGeneratedRooms);

		std::vector<Bullet> bullet;
		std::vector<Spawner> spawner;
		Hero hero(window);
		sf::View view(sf::FloatRect(hero.HeroTitle.getPosition().x, hero.HeroTitle.getPosition().y, window.getSize().x * scale, window.getSize().y * scale));
		sf::View viewminimap(sf::FloatRect(hero.HeroTitle.getPosition().x, hero.HeroTitle.getPosition().y, window.getSize().x * 3, window.getSize().y * 3));

		while (window.isOpen())
		{
			sf::Event event;
			if (gameStage == "game" || gameStage == "MiniMap")
			{
				hero.updateMouseDirection(window);
				hero.move(level.allGeneratedRooms, window);
				view.setCenter(hero.HeroTitle.getPosition().x, hero.HeroTitle.getPosition().y);

				for (int i = 0; i < level.allGeneratedRooms[level.heroCurrentRoom].enemies.size(); i++)
				{
					level.allGeneratedRooms[level.heroCurrentRoom].enemies[i]->shoot(bullet, hero, level.allGeneratedRooms[level.heroCurrentRoom].wallTitle);
					level.allGeneratedRooms[level.heroCurrentRoom].enemies[i]->move(hero, level.allGeneratedRooms[level.heroCurrentRoom].enemies, i, mapGen.walls, level.allGeneratedRooms[level.heroCurrentRoom].wallTitle, bullet);
				}

				for (int i = 0; i < bullet.size(); i++)
				{
					int h = bullet[i].move(level.allGeneratedRooms[level.heroCurrentRoom].wallTitle);
					if (h == 0)
						bullet.erase(bullet.begin() + i);
				}

				hero.collision(level.allGeneratedRooms[level.heroCurrentRoom].enemies, bullet);
				if (hero.health <= 0)
					gameStage = "EndMenu";
			}
			while (window.pollEvent(event))
			{
				if (event.type == event.MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left && gameStage == "game")
				{
					hero.shoot(window, bullet);
				}

				if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape && gameStage == "game")
					gameStage = "GameMenu";

				else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Escape && gameStage == "GameMenu")
					gameStage = "game";

			
				if (event.type == sf::Event::KeyPressed && event.key.code == sf::Keyboard::Tab && gameStage == "game")
					gameStage = "MiniMap";

				else if (event.type == sf::Event::KeyReleased && event.key.code == sf::Keyboard::Tab && gameStage == "MiniMap")
				{
					gameStage = "game"; 
					minimap.n = 0;
				}

				if (event.type == sf::Event::Closed)
				{
					window.close();
					return 0;
				}
			}
			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::LControl) && gameStage == "game")
				level.allGeneratedRooms[level.heroCurrentRoom].enemies.clear();
			
			if (gameStage == "game")
				level.spawnEnemy_and_update(hero, mapGen.walls, allField);
			
			window.setView(view);
		
			mainmenu.setPosition(window);
			gamemenu.setPosition(window);
			endmenu.setPosition(window);
			

			

				/*int hanBuf = handlePress(gameStage, mainmenu, gamemenu, endmenu, window);
			if (hanBuf == 0)
			return 0;
			if (hanBuf == 1)
			break;*/
			
			if (gameStage == "MainMenu")
			{
				int menuBuf = mainmenu.update(window);
				if (menuBuf == 1)
					gameStage = "game";
				if (menuBuf == 0)
				{
					window.close();
					return 0;
				}
			}

			if (gameStage == "GameMenu")
			{
				int menuBuf = gamemenu.update(window);
				if (menuBuf == 1)
					gameStage = "game";
				if (menuBuf == 0)
				{
					window.close();
					return 0;
				}
				if (menuBuf == 2)
				{
					gameStage = "game";
					break;
				}
			}

			if (gameStage == "EndMenu")
			{
				int menuBuf = endmenu.update(window);
				if (menuBuf == 0)
				{
					window.close();
					return 0;
				}
				if (menuBuf == 2)
				{
					gameStage = "game";
					break;
				}
			}



			window.clear();

			if (gameStage == "game" || gameStage == "GameMenu" || gameStage == "MiniMap")
			{
				
				for (int i = 0; i < level.allGeneratedRooms.size(); i++)
				{
					for (int j = 0; j < level.allGeneratedRooms[i].wallTitle.size(); j++)
						window.draw(level.allGeneratedRooms[i].wallTitle[j]);
				}
				if (gameStage == "game")
					level.allGeneratedRooms[level.heroCurrentRoom].spawner.draw(window);

				for (int i = 0; i < level.allGeneratedRooms[level.heroCurrentRoom].enemies.size(); i++)
					window.draw(level.allGeneratedRooms[level.heroCurrentRoom].enemies[i]->enemyTitle);
				if (hero.isDrawindUnderLevel == true)
				{
					level.draw(window);
					hero.draw(window);
				}
				if (hero.isDrawindUnderLevel == false)
				{
					hero.draw(window);
					level.draw(window);
				}

				for (int i = 0; i < bullet.size(); i++)
				{
					window.draw(bullet[i].bulletTitle);
				}
			
				healthText.setString(std::to_string(hero.health));
				//healthText.setString(std::to_string((int)(1.f / fps.getElapsedTime().asSeconds())));
				fps.restart();
				healthText.setFont(font);
				healthText.setCharacterSize(40);
				healthText.setPosition(window.mapPixelToCoords(sf::Vector2i(40, 40)));
				window.draw(healthText);
			}
			if (gameStage == "MainMenu")
				mainmenu.draw(window);
			if (gameStage == "GameMenu")
				gamemenu.draw(window);
			if (gameStage == "EndMenu")
				endmenu.draw(window);

			
			if (gameStage == "MiniMap")
			{
				if (minimap.n == 0)
					viewminimap.setCenter(hero.HeroTitle.getPosition().x, hero.HeroTitle.getPosition().y);
				minimap.update(window, viewminimap);
				window.setView(viewminimap);
				
				minimap.draw(level, hero, window);
				minimap.n++;
			}
			window.display();
		}
	}
	return 0;
}

