#include "Animation.h"

Animation::Animation()
{}
Animation::Animation(std::string fileName)
{
	texture.loadFromFile(fileName);
	currentFrame = 0;
	currentUpdate = 0;
}
void Animation::update(sf::Sprite& sprite, int frames)
{
	if (currentUpdate % 4 == 0)
		currentFrame++;

	if (currentFrame >= frames)
		currentFrame = 0;

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(currentFrame * (texture.getSize().x / frames), 0, texture.getSize().x / frames, texture.getSize().y));

	currentUpdate++;
}

void Animation::update(sf::Sprite& sprite, int frames, int delay)
{
	if (currentFrame != 0)
	{
		if (currentUpdate % 4 == 0)
			currentFrame++;

		if (currentFrame >= frames)
			currentFrame = 0;
	}
	else if (currentUpdate > delay * 60)
	{
		currentFrame++;
		currentUpdate = 0;
	}

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(currentFrame * (texture.getSize().x / frames), 0, texture.getSize().x / frames, texture.getSize().y));

	currentUpdate++;
}
void Animation::update(sf::Sprite& sprite, int frames, int fps, std::string lolkekChebyrek)
{
	int buf = 60 / fps;
	if (currentUpdate % buf == 0)
		currentFrame++;

	if (currentFrame >= frames)
		currentFrame = 0;

	sprite.setTexture(texture);
	sprite.setTextureRect(sf::IntRect(currentFrame * (texture.getSize().x / frames), 0, texture.getSize().x / frames, texture.getSize().y));

	currentUpdate++;
}
