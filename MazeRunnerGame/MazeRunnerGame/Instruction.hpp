#pragma once

#include "Display.hpp"
#include <string>

class Instruction :public Display
{
public:
	Instruction(float width, float height);
public:
	virtual void draw(sf::RenderWindow& window);
};