#include "MainMenu.h"


MainMenu::MainMenu(sf::RenderWindow& window)
{

	font.loadFromFile("Resourses/font.otf");
	playText.setFont(font);
	playText.setString("Play");
	playText.setCharacterSize(60);
	playText.setOrigin(playText.getGlobalBounds().width / 2, playText.getGlobalBounds().height / 2);

	exitText.setFont(font);
	exitText.setString("Exit");
	exitText.setCharacterSize(60);
	exitText.setOrigin(exitText.getGlobalBounds().width / 2, exitText.getGlobalBounds().height / 2);
}

void MainMenu::setPosition(sf::RenderWindow& window)
{
	playText.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 4 + 64)));
	exitText.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 4 + window.getSize().y / 2 - 64)));
}

void MainMenu::draw(sf::RenderWindow& window)
{
	window.draw(playText);
	window.draw(exitText);
}

int MainMenu::update(sf::RenderWindow& window)
{
	if (playText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		playText.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return 1;
	}
	else
		playText.setFillColor(sf::Color::White);

	if (exitText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		exitText.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return 0;
	}
	else 
		exitText.setFillColor(sf::Color::White);
	return 10;
}
