#pragma once

#include "Display.hpp"
#include <string>

class NextStage :public Display
{
private:
	sf::Font font;

public:
	NextStage();
	virtual ~NextStage();
};