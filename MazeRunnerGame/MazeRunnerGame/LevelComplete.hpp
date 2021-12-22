#pragma once

#include "Display.hpp"
#include "Text.hpp"
#include <string>
#include <sstream>

class LevelComplete :public Display
{
private:
	sf::Font font;
	MyText smallText[2];

public:
	LevelComplete();
	virtual ~LevelComplete();

public:
	void draw(sf::RenderWindow& window, int time);
};