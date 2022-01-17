#pragma once

#include "Display.hpp"
#include <string>

class GameOver :public Display
{

public:
	GameOver();
	GameOver(float width, float height);
	virtual ~GameOver();

public:
	void draw(sf::RenderWindow &window);
};