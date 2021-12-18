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
protected:
	sf::Texture curTexure;
	sf::RectangleShape shape;

	MazeCoordinate curMazePosition;

protected:
	virtual void initVariables();
	virtual void initShape();

public:
	//Getter - Lấy tọa độ trong cửa sổ window
	float getPositionX() const;
	float getPositionY() const;

	MazeCoordinate getPosition() {
		return curMazePosition;
	}

	//Setter - Thay đổi tích chất 
	void setPosition(float, float);
	void setColor(sf::Color);
	void setSize(float, float);
	void setOutLine(float, sf::Color);
public:
	MazeObject(float x = 0.f, float y = 0.f);
	MazeObject(MazeCoordinate pos) {
		curMazePosition = pos;
	}
	
	//Cập nhật, dựng hình
	void update(const sf::RenderTarget* target);
	void render(sf::RenderTarget* target);
};

