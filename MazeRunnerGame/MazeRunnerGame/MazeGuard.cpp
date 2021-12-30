#include "MazeGuard.hpp"

bool MazeGuard::checkLoadImage = false;
sf::Image MazeGuard::guardImage[4];
MazeGuard::MazeGuard(std::shared_ptr<Room> setRoom, MazeCoordinate posRoom, float xOffset, float yOffset, float width, float height) :
	guardCenterRoom(setRoom),
	guardCurRoom(setRoom),
	MazeObject(posRoom, xOffset, yOffset, width, height)
{
	if (checkLoadImage == false)
	{
		guardImage[0].loadFromFile(IMG_GUARD_RIGHT);
		guardImage[1].loadFromFile(IMG_GUARD_LEFT);
		guardImage[2].loadFromFile(IMG_GUARD_DOWN);  //IS CENTER
		guardImage[3].loadFromFile(IMG_GUARD_UP);
	}
	sf::Image newImage;
	newImage.create(width, height, sf::Color::Black);
	Room::resizeImage(guardImage[2], newImage);
	curTexure.loadFromImage(newImage);

	direction = rand() % 4 + 1;
}

MazeGuard::~MazeGuard()
{
}
void MazeGuard::changeDirectionImg(int a) {
	sf::Image newImage;
	newImage.create(width, height, sf::Color::Black);
	if (a == 0) {
		Room::resizeImage(guardImage[0], newImage);
	}
	else if (a == 1) {
		Room::resizeImage(guardImage[1], newImage);
	}
	else if (a == 2) {
		Room::resizeImage(guardImage[2], newImage);
	}
	else if (a == 3) {
		Room::resizeImage(guardImage[3], newImage);
	}
	curTexure.loadFromImage(newImage);
}
//Updates Guard Location Each Cycle
void MazeGuard::NextCycle()
{
	srand(time(0));
	//Find current guard room
	auto roomTypesIter = std::find(begin(guardCurRoom->roomTypes), end(guardCurRoom->roomTypes), GUARD);

	//Remove the "Guard" type from the roomTypes
	if (roomTypesIter != end(guardCurRoom->roomTypes))
		guardCurRoom->roomTypes.erase(roomTypesIter);

	MazeCoordinate posCur = guardCurRoom->roomPos;

	if (direction == 1) {
		std::shared_ptr<Room> guardCurRoomNew = guardCurRoom->checkPosConnectRoom(MazeCoordinate(posCur.getX() - 1, posCur.getY()));

		if (guardCurRoomNew != NULL) {
			if (guardCurRoomNew == guardCenterRoom) {
				while (direction == 1) {
					direction = rand() % 4 + 1;
				}
			}
			guardCurRoom = guardCurRoomNew;
			changeDirectionImg(1);
		}
		else {
			direction = 2;
		}
	}
	else if (direction == 2) {
		std::shared_ptr<Room> guardCurRoomNew = guardCurRoom->checkPosConnectRoom(MazeCoordinate(posCur.getX() + 1, posCur.getY()));
		
		if (guardCurRoomNew != NULL) {
			
			if (guardCurRoomNew == guardCenterRoom) {
				while (direction == 2) {
					direction = rand() % 4 + 1;
				}
			}
			guardCurRoom = guardCurRoomNew;
			changeDirectionImg(0);
		}
		
		else {
			direction = 1;
		}
	}
	else if (direction == 3) {
		std::shared_ptr<Room> guardCurRoomNew = guardCurRoom->checkPosConnectRoom(MazeCoordinate(posCur.getX(), posCur.getY() + 1));
		
		if (guardCurRoomNew != NULL) {
			
			if (guardCurRoomNew == guardCenterRoom) {
				while (direction == 3) {
					direction = rand() % 4 + 1;
				}
			}
			guardCurRoom = guardCurRoomNew;
			changeDirectionImg(2);
		}
		
		else {
			direction = 4;
		}
	}
	else if (direction == 4) {
		std::shared_ptr<Room> guardCurRoomNew = guardCurRoom->checkPosConnectRoom(MazeCoordinate(posCur.getX(), posCur.getY() - 1));
		
		if (guardCurRoomNew != NULL) {
			
			if (guardCurRoomNew == guardCenterRoom) {
				while (direction == 4) {
					direction = rand() % 4 + 1;
				}
			}
			guardCurRoom = guardCurRoomNew;
			changeDirectionImg(3);
		}
		
		else {
			direction = 3;
		}
	}
	guardCurRoom->roomTypes.push_back(GUARD);

	//Set position, image of room new will guard.
	setPosition(guardCurRoom->roomPos);
}


//Updates Guard Location Each Cycle
//void MazeGuard::NextCycle()
//{
//	//Find current guard room
//	auto roomTypesIter = std::find(begin((*guardIter)->roomTypes), end((*guardIter)->roomTypes), GUARD);
//
//	//Remove the "Guard" type from the roomTypes
//	if (roomTypesIter != end((*guardIter)->roomTypes))
//		(*guardIter)->roomTypes.erase(roomTypesIter);
//
//	//Move guard to next spot
//	std::advance(guardIter, 1);
//	if (guardIter == std::end(guardCenterRoomPtr->connectRooms))
//		guardIter = std::begin(guardCenterRoomPtr->connectRooms);
//
//	//Change that room type to have "Guard"
//	(*guardIter)->roomTypes.push_back(GUARD);
//
//	//Set position, image of room new will guard.
//	setPosition((*guardIter)->roomPos);
//}

