#include"GameMenu.h"



GameMenu::GameMenu(sf::RenderWindow& window)
{

	font.loadFromFile("Resourses/font.otf");
	continueText.setFont(font);
	continueText.setString("Continue");
	continueText.setCharacterSize(40);
	continueText.setOrigin(continueText.getGlobalBounds().width / 2, continueText.getGlobalBounds().height / 2);

	restartText.setFont(font);
	restartText.setString("Restart");
	restartText.setCharacterSize(40);
	restartText.setOrigin(restartText.getGlobalBounds().width / 2, restartText.getGlobalBounds().height / 2);

	exitText.setFont(font);
	exitText.setString("Exit");
	exitText.setCharacterSize(40);
	exitText.setOrigin(exitText.getGlobalBounds().width / 2, exitText.getGlobalBounds().height / 2);

	blackShape.setFillColor(sf::Color(0, 0, 0, 240));
	blackShape.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	blackShape.setOrigin(blackShape.getGlobalBounds().width / 2, blackShape.getGlobalBounds().height / 2);
	
}

void GameMenu::setPosition(sf::RenderWindow& window)
{
	restartText.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2)));
	continueText.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 4 + 64)));
	exitText.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 4 + window.getSize().y / 2 - 64)));
	blackShape.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2)));
}
void GameMenu::draw(sf::RenderWindow& window)
{
	window.draw(blackShape);
	window.draw(continueText);
	window.draw(restartText);
	window.draw(exitText);
}

int GameMenu::update(sf::RenderWindow& window)
{
	if (continueText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		continueText.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return 1;
	}
	else
		continueText.setFillColor(sf::Color::White);

	if (restartText.getGlobalBounds().contains(window.mapPixelToCoords(sf::Mouse::getPosition(window))))
	{
		restartText.setFillColor(sf::Color::Red);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Left))
			return 2;
	}
	else 
		restartText.setFillColor(sf::Color::White);

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
