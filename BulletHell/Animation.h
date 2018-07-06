#pragma once
#include <SFML/Graphics.hpp>

class Animation
{
public:
	sf::Texture texture;
	int currentUpdate;
	int currentFrame;

	Animation();
	Animation(std::string fileName);
	
	void update(sf::Sprite& sprite, int frames);

	void update(sf::Sprite& sprite, int frames, int delay);

	void update(sf::Sprite& sprite, int frames, int fps, std::string lolkekChebyrek);
	
};