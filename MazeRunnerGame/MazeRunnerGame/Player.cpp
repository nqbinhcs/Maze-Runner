#include "Player.hpp"

#include <iostream>


void Player::initVariables()
{
	this->movementSpeed = 5.f;
}

void Player::initShape()
{
	this->object.setColor(sf::Color::Green);
	this->object.setSize(OBJECT_WIDTH, OBJECT_HEIGHT);
}

Player::Player(float x, float y)
{
	this->object.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

Player::~Player()
{

}


//Accessors
Square& Player::getObject()
{
	return object;
}



void Player::updateInput()
{
	//Keyboard input

		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
		{
			this->object.getShape().move(-this->movementSpeed, 0.f);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
		{
			this->object.getShape().move(this->movementSpeed, 0.f);
		}
		if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
		{
			this->object.getShape().move(0.f, -this->movementSpeed);
		}
		else if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
		{
			this->object.getShape().move(0.f, this->movementSpeed);
		}
}


//Hàm giữ cho đối tượng không rơi ra ngoài khung hình
void Player::updateWindowBoundsCollision(const sf::RenderTarget* target)
{
	//Print Position
	std::cout << this->object.getShape().getGlobalBounds().left << ' ' << this->object.getShape().getGlobalBounds().top << ' ' << this->object.getShape().getGlobalBounds().width << '\n';
	std::cout << this->object.getShape().getPosition().x << ' ' << this->object.getShape().getPosition().y << '\n';
	//Left
	if (this->object.getShape().getGlobalBounds().left <= 0.f)
		this->object.setPosition(0.f, this->object.getShape().getGlobalBounds().top);
	//Right
	if (this->object.getShape().getGlobalBounds().left + this->object.getShape().getGlobalBounds().width >= target->getSize().x)
		this->object.setPosition(target->getSize().x - this->object.getShape().getGlobalBounds().width, this->object.getShape().getGlobalBounds().top);
	//Top
	if (this->object.getShape().getGlobalBounds().top <= 0.f)
		this->object.setPosition(this->object.getShape().getGlobalBounds().left, 0.f);
	//Bottom
	if (this->object.getShape().getGlobalBounds().top + this->object.getShape().getGlobalBounds().height >= target->getSize().y)
		this->object.setPosition(this->object.getShape().getGlobalBounds().left, target->getSize().y - this->object.getShape().getGlobalBounds().height);
}

void Player::update(const sf::RenderTarget* target)
{
	this->updateInput();

	//Window bounds collision
	this->updateWindowBoundsCollision(target);
}

void Player::updateCorrectPosition(int direction) {
	float X = object.getPositionX();
	float Y = object.getPositionY();

	if (direction == sf::Keyboard::Left)
		X = floor(X / 50.f) * 50.f;
	if (direction == sf::Keyboard::Right)
		X = ceil(X / 50.f) * 50.f;
	if (direction == sf::Keyboard::Up)
		Y = floor(Y / 50.f) * 50.f;
	if (direction == sf::Keyboard::Down)
		Y = ceil(Y / 50.f) * 50.f;

	object.setPosition(X, Y);
}

void Player::render(sf::RenderTarget* target)
{
	target->draw(this->object.getShape());
}