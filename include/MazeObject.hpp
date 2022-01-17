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
	bool isChosenByMouse = false;

public:

	MazeCoordinate getPosition() {
		return curMazePosition;
	}

	sf::Vector2f getSize() {
		return sf::Vector2f(width, height);
	}

	void setPosition(MazeCoordinate pos) {
		curMazePosition = pos;
	}

	void setSize(float width, float height) {
		this->width = width;
		this->height = height;
	}

	bool checkMouseOver(const sf::Window& window) {
		sf::Vector2i mousePosition = sf::Mouse::getPosition(window);
		sf::Vector2i objectPosition = sf::Vector2i(
		xOffset + (int)((curMazePosition.getX()) * width),
		yOffset + (int)((curMazePosition.getY()) * height));
		return (objectPosition.x <= mousePosition.x && mousePosition.x <= objectPosition.x + width &&
			objectPosition.y <= mousePosition.y && mousePosition.y <= objectPosition.y + height);
	}

public:
	MazeObject(MazeCoordinate pos, float xOffset, float yOffset, float width, float height) {
		curMazePosition = pos;
		this->xOffset = xOffset;
		this->yOffset = yOffset;
		this->width = width;
		this->height = height;
	}
	
	void update(const sf::RenderTarget* target);
	virtual void NextCycle() {

	}
	virtual void render(sf::RenderWindow& window);
};

