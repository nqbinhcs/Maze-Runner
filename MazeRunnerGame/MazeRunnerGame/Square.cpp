#include "Square.hpp"

void Square::initVariables()
{

}

void Square::initShape()
{
	this->shape.setFillColor(sf::Color::White);
	this->shape.setSize(sf::Vector2f(OBJECT_WIDTH, OBJECT_HEIGHT));
}


Square::Square(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

sf::RectangleShape& Square::getShape()
{
	return this->shape;
}

float Square::getPositionX() const
{
	return this->shape.getPosition().x;
}

float Square::getPositionY() const
{
	return this->shape.getPosition().y;
}

void Square::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
}

void Square::setColor(sf::Color color)
{
	this->shape.setFillColor(color);
}

void Square::setSize(float width, float height)
{
	this->shape.setSize(sf::Vector2f(width, height));
}

void Square::setOutLine(float think, sf::Color color) {
	this->shape.setOutlineThickness(think);
	this->shape.setOutlineColor(sf::Color(color));
}

void Square::update(const sf::RenderTarget* target)
{
}

void Square::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

// Check if a point is in square (including points on edge)
bool Square::isInSquare(const sf::Vector2f& cord) const
{
	sf::Vector2f squareCord = shape.getPosition();
	sf::Vector2f squareSize = shape.getSize();

	return (squareCord.x <= cord.x && cord.x <= squareCord.x + squareSize.x &&
		squareCord.y <= cord.y && cord.y <= squareCord.y + squareSize.y);
}

// Check collision between two squares
bool Square::checkCollision(const Square& other, bool firstCheck) const
{
	// Coordinate and size of other square
	sf::Vector2f cord = other.shape.getPosition();
	sf::Vector2f size = other.shape.getSize();

	bool areCollided = false;

	areCollided = areCollided || isInSquare(cord);
	areCollided = areCollided || isInSquare(sf::Vector2f(cord.x + size.x, cord.y));
	areCollided = areCollided || isInSquare(sf::Vector2f(cord.x, cord.y + size.y));
	areCollided = areCollided || isInSquare(sf::Vector2f(cord.x + size.x, cord.y + size.y));

	if (firstCheck)
		areCollided = areCollided || other.checkCollision(*this, 0);

	return areCollided;
}
