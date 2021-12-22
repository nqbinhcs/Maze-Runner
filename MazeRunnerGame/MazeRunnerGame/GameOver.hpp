#pragma once

#include "Display.hpp"
#include <string>

class GameOver :public Display
{
private:
	sf::Font font;
	MyText smallText;

public:
	GameOver();
	GameOver(float width, float height);
	virtual ~GameOver();

public:
	void draw(sf::RenderWindow &window);
};