#pragma once
#ifndef Display_hpp
#define Display_hpp
#include "Text.hpp"
#include <vector>

#define IMG_GAMEOVER "Images/GameOver.png"
#define IMG_NEXTSTAGE "Images/NextStage.png"
#define IMG_LEVELCOMPLETE "Images/LevelComplete.png"
#define IMG_THEME_BACKGROUND "Images/Theme.png"
#define IMG_HELP "Images/HelpMenu.png"
#define IMG_INSTRUCTION "Images/Instruction.png"

class Display
{
protected:
	sf::Texture textureBackground;
	sf::Sprite spriteBackground;
	sf::Font font;
	MyText text;
	std::vector<MyText> smallText;

public:
	Display();
	Display(float, float);
	virtual ~Display();

	bool clickMouse(sf::Text Text, sf::RenderWindow& window);
	void setPositionText(sf::Text&, float);
	virtual void draw(sf::RenderWindow& window);
};


//@DESCR: Delay function 
//@PARAM: second.
//@RETURN: None
void delay(float second);


#endif