#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <time.h>
using namespace sf;

#include "DefinedVariables.hpp"
#include "MazeObject.hpp"

class Player : public MazeObject
{
private:
	float movementSpeed;

protected:
	void initVariables();
	void initShape();

public:
	Player(float x = 0.f, float y = 0.f);
	virtual ~Player();

	//Functions
	void updateInput(sf::Keyboard::Key direction);
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target, sf::Keyboard::Key direction);
	void render(sf::RenderTarget* target);


	void setLocaStart(int x, int y);
};