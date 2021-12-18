#pragma once

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <SFML/Window.hpp>
#include <SFML/Audio.hpp>
#include <SFML/Network.hpp>
#include <time.h>
using namespace sf;

#define IMG_PLAYER_RIGHT "Images/PlayerRight.png"
#define IMG_PLAYER_LEFT "Images/PlayerLeft.png"
#define IMG_PLAYER_UP "Images/PlayerUp.png"
#define IMG_PLAYER_DOWN "Images/PlayerDown.png"

#include "DefinedVariables.hpp"
#include "MazeObject.hpp"
#include "Room.hpp"
#include "Maze.hpp"

class Player : public MazeObject
{
private:
	static sf::Image playerImages[4];
	static bool loadPlayerImages;
	//float movementSpeed;
public:
	//MazeCoordinate posPlayer;
private:

	float xOffset;
	float yOffset;

	float widthRoomPlayer;
	float heightRoomPlayer;

protected:
	void initVariables();
	void initShape();

public:
	Player(MazeCoordinate pos, float xOffset, float yOffset, float width, float height);
	virtual ~Player();

	void setWidthPlayer(float width) {
		widthRoomPlayer = width;
	}

	void setHeightPlayer(float height) {
		heightRoomPlayer = height;
	}

	void setPosStart(MazeCoordinate posStart) {
		curMazePosition = posStart;
	}

	bool checkIsConnect(shared_ptr<Maze> curMaze, shared_ptr<Room>, MazeCoordinate posNew);


	//Functions
	void updateInput(sf::Keyboard::Key direction, shared_ptr<Maze> curMaze);
	void updateWindowBoundsCollision(const sf::RenderTarget* target);
	void update(const sf::RenderTarget* target, sf::Keyboard::Key direction, shared_ptr<Maze> curMaze);
	void render(sf::RenderTarget* target);
	void render(sf::RenderWindow& window);
	void updateDirecPlayer(int i);
};