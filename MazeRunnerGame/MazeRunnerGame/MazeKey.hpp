#include "MazeObject.hpp"
#pragma once

#define IMG_MAZEKEY "Images/Start.png"

class MazeKey :	public MazeObject
{
private:
	static bool checkLoadImage;
	static 	sf::Image keyImage;
public:
	MazeKey(MazeCoordinate pos, float xOffset, float yOffset, float width, float height);
	~MazeKey();
};

