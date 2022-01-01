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
	int totalCoin;
private:
	int timesPlayed;
	bool isLose;
private:
	static sf::Image playerImages[4];
	static bool loadPlayerImages;
public:
	Player(MazeCoordinate pos, float xOffset, float yOffset, float width, float height);
	virtual ~Player();

	bool checkIsConnect(shared_ptr<Maze> curMaze, shared_ptr<Room>, MazeCoordinate posNew);

	bool getLose() {
		return isLose;
	}
	int getTimesPlayed() {
		return timesPlayed;
	}

	void setLose(bool lose) {
		isLose = lose;
	}

	bool CollisionTrap(shared_ptr<Maze> curMaze, MazeCoordinate pos);
	bool CollisionGuard(shared_ptr<Maze> curMaze, MazeCoordinate pos);
	bool CollisionKey(shared_ptr<Maze> curMaze, MazeCoordinate pos);
	bool CollisionCoin(shared_ptr<Maze> curMaze, MazeCoordinate pos);
	bool CollisionChest(shared_ptr<Maze> curMaze, MazeCoordinate pos);

	//Functions
	void updateInput(int direction, shared_ptr<Maze> curMaze);
	void update(const sf::RenderTarget* target, int direction, shared_ptr<Maze> curMaze);
	void updateDirecPlayer(int i);
	void checkCllisionObject(shared_ptr<Maze> curMaze);

	void resetTimes(bool check) {
		if (check) {
			timesPlayed = 3;
		}
		else {
			timesPlayed -= 1;
		}
	}
	bool loseLevel() {
		if (timesPlayed == 0) {
			return true;
		}
		return false;
	}
};
