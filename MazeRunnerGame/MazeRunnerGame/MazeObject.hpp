#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "DefinedVariables.hpp"
#include "Coordinate.hpp"
#include "Room.hpp"

class MazeObject
{
protected:
	sf::Texture curTexure;
	MazeCoordinate curMazePosition;
protected:

	float xOffset;
	float yOffset;

	float width;
	float height;

public:

	MazeCoordinate getPosition() {
		return curMazePosition;
	}
	void setPosition(MazeCoordinate pos) {
		curMazePosition = pos;
	}

	void setSize(float width, float height) {
		this->width = width;
		this->height = height;
	}
public:
	MazeObject(MazeCoordinate pos, float xOffset, float yOffset, float width, float height) {
		curMazePosition = pos;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = width;
		this->height = height;
	}
	
	//Cập nhật, dựng hình
	void update(const sf::RenderTarget* target);
	virtual void NextCycle() {

	}
	virtual void render(sf::RenderWindow& window);
};

