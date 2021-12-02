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
	float getPositionX() const;
	float getPositionY() const;

	//Accessors - setter
	void setPosition(float, float);
	void setColor(sf::Color);
	void setSize(float, float);
	void setOutLine(float, sf::Color);

	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

public:
	//Other functions
	bool isInSquare(const sf::Vector2f& cord) const;
	bool checkCollision(const Square& other, bool firstCheck = true) const;
};

