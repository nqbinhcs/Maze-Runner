#pragma once

#include "Display.hpp"
#include "Text.hpp"
#include <string>
#include <sstream>

class LevelComplete :public Display
{

public:
	LevelComplete();
	virtual ~LevelComplete();

public:
	void draw(sf::RenderWindow& window, int time);
};