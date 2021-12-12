#include "Room.hpp"
#include <windows.h>
#include <stdio.h>

sf::Texture Room::roomTextures[16];
bool Room::isTextureNull = true;

Room::Room(MazeCoordinate pos) : roomPos(pos)
{
	if (Room::isTextureNull == true)
	{
		Room::isTextureNull = false;

		Room::roomTextures[0b0000].loadFromFile(IMG_0BORDER); 	//None
		Room::roomTextures[0b0001].loadFromFile(IMG_1BORDER_D); 	//Down
		Room::roomTextures[0b0010].loadFromFile(IMG_1BORDER_L); //Left
		Room::roomTextures[0b0100].loadFromFile(IMG_1BORDER_U);	//Up
		Room::roomTextures[0b1000].loadFromFile(IMG_1BORDER_R);


		Room::roomTextures[0b0011].loadFromFile(IMG_2BORDER_DL);
		Room::roomTextures[0b0101].loadFromFile(IMG_2BORDER_DU);
		Room::roomTextures[0b1001].loadFromFile(IMG_2BORDER_DR);
		Room::roomTextures[0b0110].loadFromFile(IMG_2BORDER_LU);
		Room::roomTextures[0b1010].loadFromFile(IMG_2BORDER_LR);
		Room::roomTextures[0b1100].loadFromFile(IMG_2BORDER_UR);


		Room::roomTextures[0b0111].loadFromFile(IMG_3BORDER_DLU);
		Room::roomTextures[0b1011].loadFromFile(IMG_3BORDER_DLR);
		Room::roomTextures[0b1101].loadFromFile(IMG_3BORDER_DUR);
		Room::roomTextures[0b1110].loadFromFile(IMG_3BORDER_LUR);


		Room::roomTextures[0b1111].loadFromFile(IMG_4BORDER);

	}
	this->curRoomTexture.setTexture(Room::roomTextures[0b1111]);
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

//@DESCR: Sưt position.
//@PARAM: None
//@RETURN: None
void Room::MakeRoomRect(int& xOffset, int& yOffset, int& xSplits, int& ySplits, const int& mazeWidth, const int& mazeHeight)
{
	curRoomTexture.setPosition(xOffset + (int)((roomPos.getX()) * ceil(mazeWidth / xSplits)),
							   yOffset + (int)((roomPos.getY()) * ceil(mazeHeight / ySplits)));

	curRoomTexture.setOrigin((int)ceil(mazeWidth / (xSplits)),
							(int)ceil(mazeHeight / (ySplits)));
}

void Room::MakeRoomRect() {
	curRoomTexture.setPosition(100, 100);
	curRoomTexture.setOrigin(16, 16);
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
	curRoomTexture.setTexture(roomTextures[wallDirBit]);
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
//@PARAM: target(mean window), delay: const 0
//@RETURN: None
void Room::AddRoomToRenderer(int delay, sf::RenderWindow& target)
{
	/*if (delay > 0)
	{*/
		sf::sleep(sf::seconds(delay));
		target.draw(curRoomTexture);
	/*}*/
}

//@DESCR: Draw cell(room) on window.
//@PARAM: target(mean window).
//@RETURN: None
void Room::AddRoomToRenderer(sf::RenderWindow& target)
{
	//Sleep(2);
	//target.draw(curRoomTexture);
	AddRoomToRenderer(0, target);
}
