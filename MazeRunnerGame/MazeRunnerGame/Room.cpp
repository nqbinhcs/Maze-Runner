#include "Room.h"

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


void Room::MakeRoomRect(int& xOffset, int& yOffset, int& xSplits, int& ySplits, const int& mazeWidth, const int& mazeHeight)
{
	curRoomTexture.setPosition(xOffset + (int)((roomPos.getX()) * ceil(mazeWidth / xSplits)), yOffset + (int)((roomPos.getY()) * ceil(mazeHeight / ySplits)));
	curRoomTexture.setOrigin((int)ceil(mazeWidth / (xSplits)), (int)ceil(mazeHeight / (ySplits)));
}

void Room::MakeRoomRect() {
	curRoomTexture.setPosition(100, 100);
	curRoomTexture.setOrigin(16, 16);
}

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

void Room::AssignRoomTextures()
{
	curRoomTexture.setTexture(roomTextures[wallDirBit]);
}

void Room::RemoveWallDirection(std::shared_ptr<Room>& roomToConnectPtr)
{
	directions dirToRemove = CheckAdjRoomDir(*roomToConnectPtr);
	wallDirBit -= dirToRemove;
}

void Room::ConnectRoom(std::shared_ptr<Room>& roomToConnectPtr)
{
	connectRooms.push_back(roomToConnectPtr);
	RemoveWallDirection(roomToConnectPtr);
}

void Room::AddRoomToRenderer(int delay, sf::RenderWindow& target)
{
	//roomRender là màn hình mình vẽ lên
	//curRoomTexture là hình vẽ của nó
	//roomRect là hình dạng của nó
	if (delay > 0)
	{
		sf::sleep(sf::seconds(delay));
		target.draw(curRoomTexture);
	}
}

void Room::AddRoomToRenderer(sf::RenderWindow& target)
{
	target.draw(curRoomTexture);
	//AddRoomToRenderer(1, target);
}
