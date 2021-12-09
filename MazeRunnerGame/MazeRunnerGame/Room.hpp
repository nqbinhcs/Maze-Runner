#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include "DefinedVariables.hpp"

#include "Coordinate.hpp"
#include "MazeObject.hpp"

using namespace std;

enum Direction
{
	NORTH,
	SOUTH,
	EAST,
	WEST
};

enum RoomType
{
	NONE,
	START,
	END
};


//Lớp thay thế cho Cell
//Tui chưa cài cpp nha :p
class Room
{
private:
	shared_ptr<MazeObject> curDisplayMazeObject;
	sf::Texture curTexure;
	RoomType curRoomType;

	shared_ptr<Room> sideRoom[4];
	bool isTopWall;
	bool isBottomWall;
	bool isLeftWall;
	bool isRightWall;
	bool isVisited;

public:
	Room();
	~Room();

	//Mấy ông coi thử giúp tui cách sài shared_ptr như vầy chuẩn chưa nha ._. 
	shared_ptr<Room> getSide(Direction) const;
	RoomType getRoomType() const;

	void setSide(Direction, shared_ptr<Room>);
	void setRoomType(RoomType);

	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

};

