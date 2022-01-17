#include "MazeCoin.hpp"
#include "Room.hpp"

bool MazeCoin::checkLoadImage = false;
sf::Image MazeCoin::coinImage;

MazeCoin::MazeCoin(MazeCoordinate pos, float xOffset, float yOffset, float width, float height) : MazeObject(pos, xOffset, yOffset, width, height) {
	if (checkLoadImage == false) {
		coinImage.loadFromFile(IMG_MAZECOIN);
	}
	sf::Image newImage;
	newImage.create(width, height, sf::Color::Black);
	Room::resizeImage(coinImage, newImage);
	curTexure.loadFromImage(newImage);
}
MazeCoin::~MazeCoin() {

}
