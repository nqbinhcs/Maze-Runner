#include "MazeObject.hpp"
#pragma once

#define IMG_MAZECOIN "Images/Coin.png"

class MazeCoin : public MazeObject
{
private:
	static bool checkLoadImage;
	static 	sf::Image coinImage;
public:
	MazeCoin(MazeCoordinate pos, float xOffset, float yOffset, float width, float height);
	~MazeCoin();
};

