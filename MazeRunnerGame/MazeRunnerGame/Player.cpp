#include "Player.hpp"
#include <iostream>
#include<windows.h>

sf::Image Player::playerImages[4];
bool Player::loadPlayerImages = false;

//@DESCR: Initialize player's parameters
//@PARAM: None
//@RETURN: None
void Player::initVariables()
{
	//this->movementSpeed = SIZE_CELL;
}

//@DESCR: Initialize shape's parameters
//@PARAM: None
//@RETURN: None
void Player::initShape()
{
	this->setColor(sf::Color::Green);
	this->shape.setSize(sf::Vector2f(OBJECT_WIDTH, OBJECT_HEIGHT));
}

//@DESCR: Parameter constructor of Player
//@PARAM: Player's coordinate (x, y)
//@RETURN: None
Player::Player(MazeCoordinate pos, float xOffset, float yOffset, float width, float height) : MazeObject(pos), widthRoomPlayer(width), heightRoomPlayer(height), xOffset(xOffset), yOffset(yOffset)
{
	if (loadPlayerImages == false)
	{
		loadPlayerImages = true;
		playerImages[0].loadFromFile(IMG_PLAYER_LEFT);
		playerImages[1].loadFromFile(IMG_PLAYER_DOWN);
		playerImages[2].loadFromFile(IMG_PLAYER_UP);
		playerImages[3].loadFromFile(IMG_PLAYER_RIGHT);
	}
	sf::Image newImage;
	newImage.create(widthRoomPlayer, heightRoomPlayer, sf::Color::Black);
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

void Player::updateInput(sf::Keyboard::Key direction, shared_ptr<Maze> curMaze)
{
	shared_ptr<Room> roomNow = curMaze->FindRoomByPos(curMazePosition);
	switch (direction)
	{
	case sf::Keyboard::Key::Left:
		//MazeCoordinate posNew(posPlayer.getX() - 1, posPlayer.getY());
		if (curMazePosition.getX() - 1 >= 0 && checkIsConnect(curMaze, roomNow, MazeCoordinate(curMazePosition.getX() - 1, curMazePosition.getY()))) {
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
			updateDirecPlayer(1);
			curMazePosition.setY(curMazePosition.getY() + 1);
			//this->shape.move(sf::Vector2f(0.f, movementSpeed));
		}
		else {
			cout << "Can't move down.\n";
		}
		break;
	}
}


//Hàm giữ cho đối tượng không rơi ra ngoài khung hình
void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	// Debug Player's position
	std::cout << this->shape.getGlobalBounds().left << ' '
		<< this->shape.getGlobalBounds().top << ' '
		<< this->shape.getGlobalBounds().width << ' '
		<< this->shape.getGlobalBounds().height << '\n';

	std::cout << this->getPositionX() << ' ' << this->getPositionY() << '\n';
	
	// Left
	if (this->shape.getGlobalBounds().left <= 0.f)
		this->setPosition(0.f, this->shape.getGlobalBounds().top);
	// Right
	if (this->shape.getGlobalBounds().left + this->shape.getGlobalBounds().width >= target->getSize().x)
		this->setPosition(target->getSize().x - this->shape.getGlobalBounds().width, this->shape.getGlobalBounds().top);
	// Top
	if (this->shape.getGlobalBounds().top <= 0.f)
		this->setPosition(this->shape.getGlobalBounds().left, 0.f);
	// Bottom
	if (this->shape.getGlobalBounds().top + this->shape.getGlobalBounds().height >= target->getSize().y)
		this->setPosition(this->shape.getGlobalBounds().left, target->getSize().y - this->shape.getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target, sf::Keyboard::Key direction, shared_ptr<Maze> curMaze)
{
	this->updateInput(direction, curMaze);
	//Window bounds collision
	//this->updateWindowBoundsCollision(target);

}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Player::render(sf::RenderWindow& window) {
	sf::Sprite curRoomSprite(curTexure);
	//curRoomSprite.setPosition(getPositionX(), getPositionY());
	curRoomSprite.setPosition(xOffset + (int)((curMazePosition.getX()) * widthRoomPlayer), yOffset + (int)((curMazePosition.getY()) * heightRoomPlayer));
	window.draw(curRoomSprite);
}

void Player::updateDirecPlayer(int i) {
	sf::Image newImage;
	newImage.create(widthRoomPlayer, heightRoomPlayer, sf::Color::Black);
	Room::resizeImage(playerImages[i], newImage);
	curTexure.loadFromImage(newImage);
}