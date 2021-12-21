#include "MazeKey.hpp"
#include "Room.hpp"

bool MazeKey::checkLoadImage = false;
sf::Image MazeKey::keyImage;

MazeKey::MazeKey(MazeCoordinate pos, float xOffset, float yOffset, float width, float height) : MazeObject(pos, xOffset, yOffset, width, height) {
	if (checkLoadImage == false) {
		keyImage.loadFromFile(IMG_MAZEKEY);
	}
	sf::Image newImage;
	newImage.create(width, height, sf::Color::Black);
	Room::resizeImage(keyImage, newImage);
	curTexure.loadFromImage(newImage);
}
MazeKey::~MazeKey() {

}
