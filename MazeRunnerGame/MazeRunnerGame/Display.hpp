#pragma once
#ifndef Display_hpp
#define Display_hpp
#include "Text.hpp"

#define IMG_GAMEOVER "Images/GameOver.png"
#define IMG_NEXTSTAGE "Images/NextStage.png"
#define IMG_LEVELCOMPLETE "Images/LevelComplete.png"
#define IMG_THEME_BACKGROUND "Images/Theme.png"

class Display
{
protected:
	sf::Texture textureBackground;
	sf::Sprite spriteBackground;
	sf::Font fontGameName;
	sf::Text gameName;

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