#include "MazeTrap.hpp"

bool MazeTrap::loadPlayerImages = false;
sf::Image MazeTrap::trapActiveTexture;
sf::Image MazeTrap::trapInactiveTexture;

MazeTrap::MazeTrap(MazeCoordinate pos, float xOffset, float yOffset, float width, float height) :
	MazeObject(pos, xOffset, yOffset, width, height), maxTrapTime(rand() % 4 + 3), curTrapTime(rand() % maxTrapTime)
{
	isActive = false;
	if (loadPlayerImages == false)
	{
		trapActiveTexture.loadFromFile(IMG_TRAP_ACTIVE);
		trapInactiveTexture.loadFromFile(IMG_TRAP_INACTIVE);
	}
	sf::Image newImage;
	newImage.create(width, height, sf::Color::Black);
	Room::resizeImage(trapInactiveTexture, newImage);
	curTexure.loadFromImage(newImage);
	SetTrapTexture();
}

MazeTrap::~MazeTrap()
{
}
//Increments trap time and checks if trap state must change each cycle
void MazeTrap::NextCycle()
{
	curTrapTime++;
	if (curTrapTime > maxTrapTime)
	{
		curTrapTime = 0;
	}
	SetTrapTexture();
}

//Sets trap texture based off of current trap state
void MazeTrap::SetTrapTexture()
{
	if (curTrapTime == 0)
	{
		sf::Image newImage;
		newImage.create(width, height, sf::Color::Black);
		Room::resizeImage(trapActiveTexture, newImage);
		curTexure.loadFromImage(newImage);
		isActive = true;
	}
	else
	{
		sf::Image newImage;
		newImage.create(width, height, sf::Color::Black);
		Room::resizeImage(trapInactiveTexture, newImage);
		curTexure.loadFromImage(newImage);
		isActive = false;
	}
}
