#pragma once
#include "MazeObject.hpp"
#include "Room.hpp"

#define IMG_GUARD_RIGHT "Images/Guard_Right.png"
#define IMG_GUARD_LEFT "Images/Guard_Left.png"
#define IMG_GUARD_DOWN "Images/Guard_Down.png"
#define IMG_GUARD_UP "Images/Guard_Up.png"
class MazeGuard : public MazeObject
{
private:
	static bool checkLoadImage;
	static sf::Image guardImage[4];
private:
	std::shared_ptr<Room> guardCenterRoom;
	std::shared_ptr<Room> guardCurRoom;
public:
	int direction;  // 1: left; 2: right; 3: up; 4: down
public:

	MazeGuard(std::shared_ptr<Room> setRoom, MazeCoordinate posRoom, float xOffset, float yOffset, float width, float height);
	~MazeGuard();

	void changeDirectionImg(int a);
	void updateDirection(int dir) {
		while (direction != dir) {
			direction = rand() % 5;
		}
	}

	//Updates Guard Location Each Cycle
	void NextCycle();

};


