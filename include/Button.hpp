#pragma once
#include "Text.hpp"
#include <string>

#define NORMAL_BUTTON_SIZE 1
#define CHOSEN_BUTTON_SIZE 0.85

class Button
{
public:
	MyText m_Text;

	sf::Sprite m_RootSprite;
	sf::Sprite m_ScaleSprite;
	sf::Texture m_Texture;

	bool m_isChosen = false;
public:
	sf::FloatRect m_Bound;
public:
	Button() {};
	~Button() {};
public:
	void setTextBox(sf::Vector2f position, sf::Vector2f boxSize,
		sf::Color fillColor, sf::Color outlineColor,
		std::string text, std::string font,
		float textSize, sf::Uint32 style, sf::Color color);

	void setSpriteOriginToCentroid();
	void setSpriteOrigin(sf::Vector2f position);
	void setSpritePosition(sf::Vector2f position);
	void setSprite(std::string imageFile);
	void scaleSprite(float scaleSize);
	void setScaleSprite(sf::Vector2f scale);
	sf::Vector2f getScaleSprite();

public:
	void setButton(sf::Vector2f position, sf::Vector2f boxSize,
		sf::Color fillColor, sf::Color outlineColor,
		std::string text, std::string font,
		float textSize, sf::Uint32 style, sf::Color color,
		std::string imageFile = "");
	void setButton(sf::Vector2f position, std::string imageFile, float spriteScale = 1);

	void updateBound();
	void scale(float scaleSize);

	bool isClick(sf::RenderWindow* pWindow);
	bool isClickV1(sf::RenderWindow* pWindow);
	bool isMouseover(sf::RenderWindow* pWindow);
	bool isMouseoverV1(sf::RenderWindow* pWindow);


	void makeChosen();
	void makeNormal();

	bool isChosen();

public:
	void drawButton(sf::RenderTarget& window);
};

