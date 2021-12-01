#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "DefinedVariables.hpp"

class Square
{
private:
	sf::RectangleShape shape;

	//Khởi tạo các biến
	void initVariables();
	//Khởi tạo hình thái
	void initShape();

public:
	Square(float x = 0.f, float y = 0.f);

	//Accessors - getter
	sf::RectangleShape& getShape();
	float getPositionX();
	float getPositionY();

	//Accessors - setter
	void setPosition(float, float);
	void setColor(sf::Color);
	void setSize(float, float);
	void setOutLine(float, sf::Color);

	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

