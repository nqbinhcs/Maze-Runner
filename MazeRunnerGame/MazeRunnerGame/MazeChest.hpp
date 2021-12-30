#include "MazeObject.hpp"
#pragma once

#define IMG_MAZE_CHEST_START "Images/Chest.png"
#define IMG_MAZE_CHEST_WIN "Images/Chest.png"

class MazeChest : public MazeObject
{
private:
	static bool checkLoadImage;
	static 	sf::Image chestImage[];

public:
	MazeChest(MazeCoordinate pos, float xOffset, float yOffset, float width, float height);
	~MazeChest();
};

