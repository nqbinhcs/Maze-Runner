#pragma once
#include "SFML/Graphics.hpp"
#include <string>
#include "DefinedVariables.hpp"
#include <iostream>

#define FONT_GAME "Fonts/TitleFont.ttf"
#define SECOND_FONT_GAME "Fonts/GamestationCond.otf"

class MyText
{
protected:
    std::string m_strText; // chuỗi lưu các ký tự để in lên màn hình
    sf::Font m_Font;  // biến lưu font chữ
    sf::Text m_sfText; // biến Text trong sf

    sf::RectangleShape m_Box;
public:
    sf::FloatRect m_Bound;
public:
    MyText(); 
    ~MyText();
    MyText(std::string text, std::string font, float size, sf::Uint32 style, sf::Color color);

public:
    void setText(std::string text, std::string font, float size, sf::Uint32 style, sf::Color color);
    
    void setTextPosition(float posX, float posY);
    void setStyleFont(sf::Uint32 style);
    void setTextColor(sf::Color color);
    void scaleText(float scaleSize);

    void setCharacterSize(float size);
    void setCharacterSpacing(float space);

    void setFont(std::string font);

    void setContent(std::string textS);
    void updateContent();

    float getTextSize();
    float getCharacterSize();
    short getTextLength();
    float getTextHeight();
    float getTextBottom();

    float getTextPositionX();
    float getTextPositionY();

    void setTextOriginToLeft();
    void setTextOriginToCenter();
    void setTextOriginToRight();

    void setTextOriginToTop();
    void setTextOriginToMiddle();
    void setTextOriginToBottom();

public:
    void setBox(sf::Vector2f position, sf::Vector2f size, sf::Color fillColor, sf::Color outlineColor);;
    void setBoxPosition(sf::Vector2f position);
    void setBoxSize(sf::Vector2f size);
    void setBoxFillColor(sf::Color color);
    void setBoxOutlineColor(sf::Color color);
    void setBoxOutlineThickness(float thickness);
    void scaleBox(float scaleSize);

    void setBoxOriginToLeft();
    void setBoxOriginToCenter();
    void setBoxOriginToRight();

    void setBoxOriginToTop();
    void setBoxOriginToMiddle();
    void setBoxOriginToBottom();

public:
    void alignTextLeft();
    void alignTextCenter();
    void alignTextRight();

    void alignTextTop();
    void alignTextMiddle();
    void alignTextBottom();

    void alignBoxLeft();
    void alignBoxCenter();
    void alignBoxRight();
    
    void alignBoxTop();
    void alignBoxMiddle();
    void alignBoxBottom();

public:

    void updateBound();

    void rotate(float angle);
    void scale(float scaleSize);
public:
    void drawMyText(sf::RenderTarget& window);
};