#include"EndMenu.h"


EndMenu::EndMenu(sf::RenderWindow& window)
{

	font.loadFromFile("Resourses/font.otf");
	messageText.setFont(font);
	messageText.setString("You Died!");
	messageText.setCharacterSize(40);
	messageText.setOrigin(messageText.getGlobalBounds().width / 2, messageText.getGlobalBounds().height / 2);

	restartText.setFont(font);
	restartText.setString("Restart");
	restartText.setCharacterSize(40);
	restartText.setOrigin(restartText.getGlobalBounds().width / 2, restartText.getGlobalBounds().height / 2);

	exitText.setFont(font);
	exitText.setString("Exit");
	exitText.setCharacterSize(40);
	exitText.setOrigin(exitText.getGlobalBounds().width / 2, exitText.getGlobalBounds().height / 2);

	

	blackShape.setFillColor(sf::Color(0, 0, 0, 255));
	blackShape.setSize(sf::Vector2f(window.getSize().x, window.getSize().y));
	blackShape.setOrigin(blackShape.getGlobalBounds().width / 2, blackShape.getGlobalBounds().height / 2);
	
}

void EndMenu::setPosition(sf::RenderWindow& window)
{
	restartText.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2)));
	messageText.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 4 + 64)));
	exitText.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 4 + window.getSize().y / 2 - 64)));
	blackShape.setPosition(window.mapPixelToCoords(sf::Vector2i(window.getSize().x / 2, window.getSize().y / 2)));
}
void EndMenu::draw(sf::RenderWindow& window)
{
	window.draw(blackShape);
	window.draw(messageText);
	window.draw(restartText);
	window.draw(exitText);
}

int EndMenu::update(sf::RenderWindow& window)
{

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
