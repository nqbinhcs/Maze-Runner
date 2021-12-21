#include "MazeChest.hpp"
#include "Room.hpp"

bool MazeChest::checkLoadImage = false;
sf::Image MazeChest::chestImage[2];

MazeChest::MazeChest(MazeCoordinate pos, float xOffset, float yOffset, float width, float height) : MazeObject(pos, xOffset, yOffset, width, height) {
	if (checkLoadImage == false) {
		chestImage[0].loadFromFile(IMG_MAZE_CHEST_START);
		chestImage[1].loadFromFile(IMG_MAZE_CHEST_WIN);
	}
	sf::Image newImage;
	newImage.create(width, height, sf::Color::Black);
	Room::resizeImage(chestImage[0], newImage);
	curTexure.loadFromImage(newImage);
}
MazeChest::~MazeChest() {

}
