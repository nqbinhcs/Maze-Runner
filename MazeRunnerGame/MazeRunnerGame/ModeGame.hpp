#pragma once
#include "Menu.hpp"

class ModeGame :public Menu
{
private:
	sf::Text textMode[3];
	sf::Font font;
	int select;
public:
	ModeGame();
	virtual ~ModeGame();
	ModeGame(float, float);

	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();
	void mouseMoved(sf::RenderWindow& windows);
	//int mouseSelect(sf::RenderWindow& window);
	//int mouseSelectHigh(sf::RenderWindow& window);
	void runModeGame(sf::RenderWindow& window);
	//void runModeHigh(sf::RenderWindow& window);
	int GetPressedItem();
};