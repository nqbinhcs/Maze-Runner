#ifndef Menu_hpp
#define Menu_hpp
#define _MAX_CHOICE_MENU 5

#include "Display.hpp"
#include <string>

class Menu :public Display
{
private:
	int selectOption;
	sf::Font font;
	sf::Text text[_MAX_CHOICE_MENU];
	sf::Text GameTittle;

private:
	// For effect
	int delta_effect;

public:
	Menu();
	Menu(float, float);
	virtual ~Menu();

	void setText(int, std::string nameOption);
	void draw(sf::RenderWindow& window);
	void moveUp();
	void moveDown();

	void mouseMoved(sf::RenderWindow& windows);
	void mouseSelect(sf::RenderWindow& window);

	int GetPressedItem();
};

#endif /* Menu_hpp */