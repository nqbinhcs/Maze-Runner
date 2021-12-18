#include "Player.hpp"
#include <iostream>
#include<windows.h>


//@DESCR: Initialize player's parameters
//@PARAM: None
//@RETURN: None
void Player::initVariables()
{
	this->movementSpeed = SIZE_CELL;
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
Player::Player(float x, float y)
{
	this->setPosition(roundf(x * SIZE_CELL), roundf(y * SIZE_CELL));

	this->initVariables();
	this->initShape();
}

//@DESCR: Destructor of Game
//@PARAM: None
//@RETURN: None
Player::~Player()
{
}

void Player::updateInput(int direction)
{
	switch (direction)
	{
	case sf::Keyboard::Key::Left:
		this->shape.move(sf::Vector2f(-movementSpeed, 0.f));
		break;
	case sf::Keyboard::Key::Right:
		this->shape.move(sf::Vector2f(movementSpeed, 0.f));
		break;
	case sf::Keyboard::Key::Up:
		this->shape.move(sf::Vector2f(0.f, -movementSpeed));
		break;
	case sf::Keyboard::Key::Down:
		this->shape.move(sf::Vector2f(0.f, movementSpeed));
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

void Player::update(const sf::RenderTarget* target, int direction)
{
	this->updateInput(direction);

	//Window bounds collision
	this->updateWindowBoundsCollision(target);

}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

void Player::setLocaStart(int i, int j) {
	this->setPosition((i)*SIZE_CELL, (j)*SIZE_CELL);
	//this->move(x * 1.0f, y * 1.0f);
}