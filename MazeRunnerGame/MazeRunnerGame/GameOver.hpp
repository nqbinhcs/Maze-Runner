#pragma once

#include "Display.hpp"
#include <string>

class GameOver :public Display
{
private:
	sf::Font font;

public:
	GameOver();
	virtual ~GameOver();
};