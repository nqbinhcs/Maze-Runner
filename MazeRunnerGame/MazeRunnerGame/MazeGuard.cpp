#include "MazeGuard.hpp"

bool MazeGuard::checkLoadImage = false;
sf::Image MazeGuard::guardImage;

MazeGuard::MazeGuard(std::shared_ptr<Room> setRoom, MazeCoordinate posRoom, float xOffset, float yOffset, float width, float height) :
	guardCenterRoomPtr(setRoom),
	guardIter(begin(setRoom->connectRooms)),
	guardCurRoomPtr(*(begin(setRoom->connectRooms))),
	MazeObject(posRoom, xOffset, yOffset, width, height)
{
	if (checkLoadImage == false)
	{
		guardImage.loadFromFile(IMG_GUARD);
	}
	sf::Image newImage;
	newImage.create(width, height, sf::Color::Black);
	Room::resizeImage(guardImage, newImage);
	curTexure.loadFromImage(newImage);
}

MazeGuard::~MazeGuard()
{
}

//Updates Guard Location Each Cycle
void MazeGuard::NextCycle()
{
	//Find current guard room
	auto roomTypesIter = std::find(begin((*guardIter)->roomTypes), end((*guardIter)->roomTypes), GUARD);

	//Remove the "Guard" type from the roomTypes
	if (roomTypesIter != end((*guardIter)->roomTypes))
		(*guardIter)->roomTypes.erase(roomTypesIter);

	//Move guard to next spot
	std::advance(guardIter, 1);
	if (guardIter == std::end(guardCenterRoomPtr->connectRooms))
		guardIter = std::begin(guardCenterRoomPtr->connectRooms);

	//Change that room type to have "Guard"
	(*guardIter)->roomTypes.push_back(GUARD);

	//Set position, image of room new will guard.
	setPosition((*guardIter)->roomPos);
}

void MazeGuard::render(sf::RenderWindow& window) {
	sf::Sprite curRoomSprite(curTexure);
	curRoomSprite.setPosition(xOffset + (int)((curMazePosition.getX()) * width), yOffset + (int)((curMazePosition.getY()) * height));
	window.draw(curRoomSprite);
}
