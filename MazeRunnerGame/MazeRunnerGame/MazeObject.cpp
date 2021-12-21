#include "MazeObject.hpp"

void MazeObject::update(const sf::RenderTarget* target)
{
}

void MazeObject::render(sf::RenderWindow& window) {
	sf::Sprite curRoomSprite(curTexure);
	curRoomSprite.setPosition(xOffset + (int)((curMazePosition.getX()) * width), yOffset + (int)((curMazePosition.getY()) * height));
	window.draw(curRoomSprite);
}
