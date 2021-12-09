#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "DefinedVariables.hpp"
#include "Coordinate.hpp"

class MazeObject
{
private:

	sf::Texture curTexure;
	sf::RectangleShape shape;

	MazeCoordinate curMazePosition;

	void initVariables();
	void initShape();

public:
	MazeObject(float x = 0.f, float y = 0.f);

	//Getter - Lấy tọa độ trong cửa sổ window
	sf::RectangleShape& getShape();
	float getPositionX() const;
	float getPositionY() const;

	//Setter - Thay đổi tích chất 
	void setPosition(float, float);
	void setColor(sf::Color);
	void setSize(float, float);
	void setOutLine(float, sf::Color);

	//Cập nhật, dựng hình
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);

public:
	bool isInMazeObject(const sf::Vector2f& cord) const;
	bool checkCollision(const MazeObject& other, bool firstCheck = true) const;
};

