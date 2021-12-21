#include "Player.hpp"
#include <iostream>
#include<windows.h>

sf::Image Player::playerImages[4];
bool Player::loadPlayerImages = false;

//@DESCR: Parameter constructor of Player
//@PARAM: Player's coordinate (x, y)
//@RETURN: None
Player::Player(MazeCoordinate pos, float xOffset, float yOffset, float width, float height) : MazeObject(pos, xOffset, yOffset, width, height)
{
	isLose = false;
	if (loadPlayerImages == false)
	{
		loadPlayerImages = true;
		playerImages[0].loadFromFile(IMG_PLAYER_LEFT);
		playerImages[1].loadFromFile(IMG_PLAYER_DOWN);
		playerImages[2].loadFromFile(IMG_PLAYER_UP);
		playerImages[3].loadFromFile(IMG_PLAYER_RIGHT);
	}
	sf::Image newImage;
	newImage.create(width, height, sf::Color::Black);
	Room::resizeImage(playerImages[0], newImage);
	curTexure.loadFromImage(newImage);

	//this->initVariables();
	//this->initShape();
}

//@DESCR: Destructor of Game
//@PARAM: None
//@RETURN: None
Player::~Player()
{
}

bool Player::checkIsConnect(shared_ptr<Maze> curMaze, shared_ptr<Room> roomNow, MazeCoordinate posNew) {
	shared_ptr<Room> roomNew = curMaze->FindRoomByPos(posNew);
	return roomNow->checkConnectRoom(roomNew);
}

void Player::updateInput(int direction, shared_ptr<Maze> curMaze)
{
	shared_ptr<Room> roomNow = curMaze->FindRoomByPos(curMazePosition);
	switch (direction)
	{
	case sf::Keyboard::Key::Left:
		//MazeCoordinate posNew(posPlayer.getX() - 1, posPlayer.getY());
		if (curMazePosition.getX() - 1 >= 0 && checkIsConnect(curMaze, roomNow, MazeCoordinate(curMazePosition.getX() - 1, curMazePosition.getY()))) {
			CollisionTrap(curMaze, MazeCoordinate(curMazePosition.getX() - 1, curMazePosition.getY()));
			CollisionGuard(curMaze, MazeCoordinate(curMazePosition.getX() - 1, curMazePosition.getY()));
			updateDirecPlayer(0);
			curMazePosition.setX(curMazePosition.getX() - 1);
			//this->shape.move(sf::Vector2f(-movementSpeed, 0.f));
		}
		else {
			cout << "Can't move left.\n";
		}
		break;
	case sf::Keyboard::Key::Right:
		if (curMazePosition.getX() + 1 < curMaze->getNumCol() && checkIsConnect(curMaze, roomNow, MazeCoordinate(curMazePosition.getX() + 1, curMazePosition.getY()))) {
			CollisionTrap(curMaze, MazeCoordinate(curMazePosition.getX() + 1, curMazePosition.getY()));
			CollisionGuard(curMaze, MazeCoordinate(curMazePosition.getX() + 1, curMazePosition.getY()));
			updateDirecPlayer(3);
			curMazePosition.setX(curMazePosition.getX() + 1);
			//this->shape.move(sf::Vector2f(movementSpeed, 0.f));
		}
		else {
			cout << "Can't move right.\n";
		}
		break;
	case sf::Keyboard::Key::Up:
		if (curMazePosition.getY() - 1 >= 0 && checkIsConnect(curMaze, roomNow, MazeCoordinate(curMazePosition.getX(), curMazePosition.getY() - 1))) {
			CollisionTrap(curMaze, MazeCoordinate(curMazePosition.getX(), curMazePosition.getY() - 1));
			CollisionGuard(curMaze, MazeCoordinate(curMazePosition.getX(), curMazePosition.getY() - 1));
			updateDirecPlayer(2);
			curMazePosition.setY(curMazePosition.getY() - 1);
			//this->shape.move(sf::Vector2f(0.f, -movementSpeed));
		}
		else {
			cout << "Can't move up.\n";
		}
		break;
	case sf::Keyboard::Key::Down:
		if (curMazePosition.getY() + 1 < curMaze->getNumRow() && checkIsConnect(curMaze, roomNow, MazeCoordinate(curMazePosition.getX(), curMazePosition.getY() + 1))) {
			//Check if player collision trap or guard
			CollisionTrap(curMaze, MazeCoordinate(curMazePosition.getX(), curMazePosition.getY() + 1));
			CollisionGuard(curMaze, MazeCoordinate(curMazePosition.getX(), curMazePosition.getY() + 1));
			updateDirecPlayer(1);
			curMazePosition.setY(curMazePosition.getY() + 1);
			//this->shape.move(sf::Vector2f(0.f, movementSpeed));
		}
		else {
			cout << "Can't move down.\n";
		}
		break;
	}
	if (curMaze->mazeLevel >= 3) {
		curMaze->NextMazeCycle();
	}
	//Check after cycle guard or trap collision player
	CollisionTrap(curMaze, MazeCoordinate(curMazePosition.getX(), curMazePosition.getY() + 1));
	CollisionGuard(curMaze, MazeCoordinate(curMazePosition.getX(), curMazePosition.getY() + 1));
}

void Player::update(const sf::RenderTarget* target, int direction, shared_ptr<Maze> curMaze)
{
	this->updateInput(direction, curMaze);
}


void Player::updateDirecPlayer(int i) {
	sf::Image newImage;
	newImage.create(width, height, sf::Color::Black);
	Room::resizeImage(playerImages[i], newImage);
	curTexure.loadFromImage(newImage);
}


bool Player::CollisionTrap(shared_ptr<Maze> curMaze, MazeCoordinate posNew) {
	//Check collision with trap
	for (int i = 0; i < curMaze->mazeTrap.size(); i++) {
		if (curMaze->mazeTrap[i]->getActive() == true && curMaze->mazeTrap[i]->getPosition() == posNew) {
			isLose = true;
			cout << "YOU LOOSE" << endl;
			return true;
		}
	}
	return false;
}
bool Player::CollisionGuard(shared_ptr<Maze> curMaze, MazeCoordinate posNew) {
	for (int i = 0; i < curMaze->mazeGuard.size(); i++) {
		if (curMaze->mazeGuard[i]->getPosition() == posNew) {
			isLose = true;
			cout << "YOU LOOSE" << endl;
			return true;
		}
	}
	return false;
}
