#pragma once
#include <SFML/Graphics.hpp>
#include <string>
#include "DefinedVariables.hpp"
#include <iostream>

#define CHRACTER_SIZE 40
#define FONT_GAME "Fonts/TitleFont.ttf"

class TextShow
{
protected:
    std::string textS; // chuỗi lưu các ký tự để in lên màn hình

    sf::Font font;  // biến lưu font chữ
    sf::Text textT; // biến Text trong sf
    sf::Text style; // kiểu chữ

    float posX; // vị trí in ra màn hình
    float posY;

public:
    TextShow(); 
    ~TextShow();
    TextShow(std::string textS, std::string font, float posX, float posY);
    void set(std::string textS, std::string font, float posX, float posY);
    void setPosition(float posX, float posY);
    void setText(std::string textS);
    void setFont(std::string font);
    void drawText(sf::RenderWindow& window);
    void setStyleFont(int style);
    void setColor(unsigned short red, unsigned short green, unsigned short blue);
    void updateText();
    void scale(float scaleSize);
    void setSize(float size);

    float getSizeText();
    float getSizeCharacter();
    short lengthText();
    float getheight();
    float getBottom();

    float getPositionX();
    float getPositionY();

    void setOriginToMidHead();
    void setOriginToTopHead();
    void setOriginToMidle();
    void setOriginToMidTop();
};