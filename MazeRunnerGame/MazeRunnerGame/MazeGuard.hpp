#pragma once
#include "MazeObject.hpp"
#include "Room.hpp"

#define IMG_GUARD "Images/Guard.png"
class MazeGuard : public MazeObject
{
private:
	static bool checkLoadImage;
	static sf::Image guardImage;
private:
	std::shared_ptr<Room> guardCenterRoomPtr;
	std::shared_ptr<Room> guardCurRoomPtr;
	std::vector<std::shared_ptr<Room>>::iterator guardIter;

public:

	MazeGuard(std::shared_ptr<Room> setRoom, MazeCoordinate posRoom, float xOffset, float yOffset, float width, float height);
	~MazeGuard();

	//Updates Guard Location Each Cycle
	void NextCycle();
	void render(sf::RenderWindow& window);

};

