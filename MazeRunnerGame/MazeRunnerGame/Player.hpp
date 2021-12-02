#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>

#include "DefinedVariables.hpp"
#include "Square.hpp"

class Player
{
private:
	Square object;

	float movementSpeed;

	void initVariables();
	void initShape();

public:
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	//Accessors
	Square& getObject();

	//Functions
	void updateInput();
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target);
	void updateCorrectPosition(int direction);
	void render(sf::RenderTarget* target);
};