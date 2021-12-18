#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "DefinedVariables.hpp"

#include "MazeObject.hpp"
#include "Coordinate.hpp"

using namespace std;

#define IMG_4BORDER "Images/Room_4Border.png"

#define IMG_3BORDER_DLU "Images/Room_3Border_D_L_U.png"
#define IMG_3BORDER_LUR "Images/Room_3Border_L_U_R.png"
#define IMG_3BORDER_DUR "Images/Room_3Border_D_U_R.png"
#define IMG_3BORDER_DLR "Images/Room_3Border_D_L_R.png"

#define IMG_2BORDER_LU "Images/Room_2Border_L_U.png"
#define IMG_2BORDER_UR "Images/Room_2Border_U_R.png"
#define IMG_2BORDER_DL "Images/Room_2Border_D_L.png"
#define IMG_2BORDER_DR "Images/Room_2Border_D_R.png"
#define IMG_2BORDER_DU "Images/Room_2Border_D_U.png"
#define IMG_2BORDER_LR "Images/Room_2Border_L_R.png"

#define IMG_1BORDER_D "Images/Room_1Border_D.png"
#define IMG_1BORDER_L "Images/Room_1Border_L.png"
#define IMG_1BORDER_U "Images/Room_1Border_U.png"
#define IMG_1BORDER_R "Images/Room_1Border_R.png"

#define IMG_0BORDER "Images/Room_0Border.png"
//=============================================================================
#define IMG_4BORDER_END "Images/Room_4Border_End.png"

#define IMG_3BORDER_DLU_END "Images/Room_3Border_D_L_U_End.png"
#define IMG_3BORDER_LUR_END "Images/Room_3Border_L_U_R_End.png"
#define IMG_3BORDER_DUR_END "Images/Room_3Border_D_U_R_End.png"
#define IMG_3BORDER_DLR_END "Images/Room_3Border_D_L_R_End.png"

#define IMG_2BORDER_LU_END "Images/Room_2Border_L_U_End.png"
#define IMG_2BORDER_UR_END "Images/Room_2Border_U_R_End.png"
#define IMG_2BORDER_DL_END "Images/Room_2Border_D_L_End.png"
#define IMG_2BORDER_DR_END "Images/Room_2Border_D_R_End.png"
#define IMG_2BORDER_DU_END "Images/Room_2Border_D_U_End.png"
#define IMG_2BORDER_LR_END "Images/Room_2Border_L_R_End.png"

#define IMG_1BORDER_D_END "Images/Room_1Border_D_End.png"
#define IMG_1BORDER_L_END "Images/Room_1Border_L_End.png"
#define IMG_1BORDER_U_END "Images/Room_1Border_U_End.png"
#define IMG_1BORDER_R_END "Images/Room_1Border_R_End.png"

#define IMG_0BORDER_END "Images/Room_0Border_End.png"
//=============================================================================
#define IMG_4BORDER_BROWSER "Images/Room_4Border_Browser.png"

#define IMG_3BORDER_DLU_BROWSER "Images/Room_3Border_D_L_U_Browser.png"
#define IMG_3BORDER_LUR_BROWSER "Images/Room_3Border_L_U_R_Browser.png"
#define IMG_3BORDER_DUR_BROWSER "Images/Room_3Border_D_U_R_Browser.png"
#define IMG_3BORDER_DLR_BROWSER "Images/Room_3Border_D_L_R_Browser.png"

#define IMG_2BORDER_LU_BROWSER "Images/Room_2Border_L_U_Browser.png"
#define IMG_2BORDER_UR_BROWSER "Images/Room_2Border_U_R_Browser.png"
#define IMG_2BORDER_DL_BROWSER "Images/Room_2Border_D_L_Browser.png"
#define IMG_2BORDER_DR_BROWSER "Images/Room_2Border_D_R_Browser.png"
#define IMG_2BORDER_DU_BROWSER "Images/Room_2Border_D_U_Browser.png"
#define IMG_2BORDER_LR_BROWSER "Images/Room_2Border_L_R_Browser.png"

#define IMG_1BORDER_D_BROWSER "Images/Room_1Border_D_Browser.png"
#define IMG_1BORDER_L_BROWSER "Images/Room_1Border_L_Browser.png"
#define IMG_1BORDER_U_BROWSER "Images/Room_1Border_U_Browser.png"
#define IMG_1BORDER_R_BROWSER "Images/Room_1Border_R_Browser.png"

#define IMG_0BORDER_BROWSER "Images/Room_0Border_Browser.png"


enum directions {
	DOWN = 0b0001,
	LEFT = 0b0010,
	UP = 0b0100,
	RIGHT = 0b1000
};
enum RoomType
{
	NONE,
	START,
	END
};

class Room
{
public:
	static bool isTextureNull;
	static sf::Image roomImages[];
	static sf::Image roomImagesEnd[];
	static sf::Image roomImagesBrowser[];
private:
	float positionX;
	float positionY;
	float widthRoom;
	float heightRoom;
public:
	std::vector<RoomType> roomTypes;

	//Position of Rooms
	MazeCoordinate roomPos;

	//Integer that tells us what direction the walls will have
	int wallDirBit = 0b1111;

	//Tells us if the Room is in the maze
	bool inMaze = false;

	bool isBrowser = false;

	//Rooms adjacent to this room
	std::vector<std::shared_ptr<Room>> adjRooms;

	//Rooms that could be selected to connect to this room when creating the maze
	std::vector<std::shared_ptr<Room>> availRooms;

	//Rooms that are connected to the this room
	std::vector<std::shared_ptr<Room>> connectRooms;

	//MazeObject vừa là hình vừa là Texture.
	sf::Texture curRoomTexture;

public:
	static void resizeImage(const sf::Image& originalImage, sf::Image& resizedImage);

public:
	Room(MazeCoordinate pos, int widthRoom, int heightRoom/*, sf::RenderWindow& target*/);
	Room(const Room& obj);
	~Room();

	int getWidthRoom() {
		return widthRoom;
	}
	int getHeightRoom() {
		return heightRoom;
	}

	//Create Room Rect
	void MakeRoomRect(int& xOffset, int& yOffset, int& xSplits, int& ySplits, const int& mazeWidth, const int& mazeHeight);

	void MakeRoomRect();

	//Check the direction of an adjacent room
	directions CheckAdjRoomDir(Room& room);

	//Assign Texture to this room based off the number of walls (wallDirections)
	void AssignRoomTextures();
	void SetRoomEnd();
	void SetRoomBrowser();
	//Remove Wall if one is there 
	void RemoveWallDirection(std::shared_ptr<Room>& roomToConnectPtr);

	//Connect Room and Remove Wall Direction
	void ConnectRoom(std::shared_ptr<Room>& roomToConnectPtr);

	//Adds room to Renderer. If it has a delay, render after waiting. 
	void AddRoomToRenderer(sf::RenderWindow& target);

	bool checkConnectRoom(std::shared_ptr<Room> isRoomConnect);
};

