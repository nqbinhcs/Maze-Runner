#include "Room.hpp"
#include <windows.h>
#include <stdio.h>
#include <iostream>

sf::Image Room::roomImages[16];
bool Room::isTextureNull = true;

Room::Room(MazeCoordinate pos, int widthRoom, int heightRoom) : roomPos(pos), widthRoom(widthRoom), heightRoom(heightRoom)
{
	if (Room::isTextureNull == true)
	{
		Room::isTextureNull = false;


		Room::roomImages[0b0000].loadFromFile(IMG_0BORDER); 	//None
		Room::roomImages[0b0001].loadFromFile(IMG_1BORDER_D); 	//Down
		Room::roomImages[0b0010].loadFromFile(IMG_1BORDER_L);	//Left
		Room::roomImages[0b0100].loadFromFile(IMG_1BORDER_U);	//Up
		Room::roomImages[0b1000].loadFromFile(IMG_1BORDER_R);

		Room::roomImages[0b0011].loadFromFile(IMG_2BORDER_DL);
		Room::roomImages[0b0101].loadFromFile(IMG_2BORDER_DU);
		Room::roomImages[0b1001].loadFromFile(IMG_2BORDER_DR);
		Room::roomImages[0b0110].loadFromFile(IMG_2BORDER_LU);
		Room::roomImages[0b1010].loadFromFile(IMG_2BORDER_LR);
		Room::roomImages[0b1100].loadFromFile(IMG_2BORDER_UR);

		Room::roomImages[0b0111].loadFromFile(IMG_3BORDER_DLU);
		Room::roomImages[0b1011].loadFromFile(IMG_3BORDER_DLR);
		Room::roomImages[0b1101].loadFromFile(IMG_3BORDER_DUR);
		Room::roomImages[0b1110].loadFromFile(IMG_3BORDER_LUR);

		Room::roomImages[0b1111].loadFromFile(IMG_4BORDER);
	}
	sf::Image newImage;
	newImage.create(widthRoom, heightRoom, sf::Color::Black);
	resizeImage(roomImages[0b1111], newImage);
	curRoomTexture.loadFromImage(newImage);
}

Room::Room(const Room& other) :
	roomPos(other.roomPos),
	curRoomTexture(other.curRoomTexture),
	adjRooms(other.adjRooms),
	availRooms(other.availRooms),
	connectRooms(other.connectRooms)
{

}

Room::~Room()
{
	
}

//@DESCR: Set position.
//@PARAM: None
//@RETURN: None
void Room::MakeRoomRect(int& xOffset, int& yOffset, int& xSplits, int& ySplits, const int& mazeWidth, const int& mazeHeight)
{
	positionX = xOffset + (int)((roomPos.getX()) * ceil(mazeWidth / xSplits));
	positionY = yOffset + (int)((roomPos.getY()) * ceil(mazeHeight / ySplits));
	widthRoom = (int)ceil(mazeWidth / (xSplits));
	heightRoom = (int)ceil(mazeHeight / (ySplits));
}

//@DESCR: NOT UNDERSTAND,
//@PARAM: None
//@RETURN: None
directions Room::CheckAdjRoomDir(Room& room)
{
	directions dir;
	if (roomPos.getX() == room.roomPos.getX())
	{
		if (roomPos.getY() < room.roomPos.getY())
			dir = DOWN;
		else if (roomPos.getY() > room.roomPos.getY())
			dir = UP;
	}
	else if (roomPos.getY() == room.roomPos.getY())
	{
		if (roomPos.getX() < room.roomPos.getX())
			dir = RIGHT;

		else if (roomPos.getX() > room.roomPos.getX())
			dir = LEFT;
	}
	return dir;
}

//@DESCR: Set images of Roo,
//@PARAM: None
//@RETURN: None
void Room::AssignRoomTextures()
{
	sf::Image newImage;
	newImage.create(widthRoom, heightRoom, sf::Color::Black);
	resizeImage(roomImages[wallDirBit], newImage);
	curRoomTexture.loadFromImage(newImage);
}
//@DESCR: Remove wall direction. (not understand)
//@PARAM: shared_ptr<Room>
//@RETURN: None
void Room::RemoveWallDirection(std::shared_ptr<Room>& roomToConnectPtr)
{
	directions dirToRemove = CheckAdjRoomDir(*roomToConnectPtr);
	wallDirBit -= dirToRemove;
}

//@DESCR: Connect room this with room other.
//@PARAM: shared_ptr<Room>
//@RETURN: None
void Room::ConnectRoom(std::shared_ptr<Room>& roomToConnectPtr)
{
	connectRooms.push_back(roomToConnectPtr);
	RemoveWallDirection(roomToConnectPtr);
}

//@DESCR: Draw cell(room) on window.
//@PARAM: target(mean window).
//@RETURN: None
void Room::AddRoomToRenderer(sf::RenderWindow& window)
{
	sf::Sprite curRoomSprite(curRoomTexture);
	curRoomSprite.setPosition(positionX, positionY);
	window.draw(curRoomSprite);
}

//@DESCR: Use resize images.
//@PARAM: None.
//@RETURN: None
void Room::resizeImage(const sf::Image& originalImage, sf::Image& resizedImage)
{
	const sf::Vector2u originalImageSize{ originalImage.getSize() };
	const sf::Vector2u resizedImageSize{ resizedImage.getSize() };
	for (unsigned int y{ 0u }; y < resizedImageSize.y; ++y)
	{
		for (unsigned int x{ 0u }; x < resizedImageSize.x; ++x)
		{
			unsigned int origX{ static_cast<unsigned int>(static_cast<double>(x) / resizedImageSize.x * originalImageSize.x) };
			unsigned int origY{ static_cast<unsigned int>(static_cast<double>(y) / resizedImageSize.y * originalImageSize.y) };
			resizedImage.setPixel(x, y, originalImage.getPixel(origX, origY));
		}
	}
}

bool Room::checkConnectRoom(std::shared_ptr<Room> isRoomConnect) {
	if (connectRooms.size() == 0) {
		return false;
	}
	else {
		for (int i = 0; i < connectRooms.size(); i++) {
			if (connectRooms[i] == isRoomConnect) {
				return true;
			}
		}
	}
	return false;
}
