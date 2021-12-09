#include "MazeObject.hpp"

void MazeObject::initVariables()
{

}

void MazeObject::initShape()
{
	this->shape.setFillColor(sf::Color::White);
	this->shape.setSize(sf::Vector2f(OBJECT_WIDTH, OBJECT_HEIGHT));
}


MazeObject::MazeObject(float x, float y)
{
	this->shape.setPosition(x, y);

	this->initVariables();
	this->initShape();
}

sf::RectangleShape& MazeObject::getShape()
{
	return this->shape;
}

float MazeObject::getPositionX() const
{
	return this->shape.getPosition().x;
}

float MazeObject::getPositionY() const
{
	return this->shape.getPosition().y;
}

void MazeObject::setPosition(float x, float y)
{
	this->shape.setPosition(x, y);
}

void MazeObject::setColor(sf::Color color)
{
	this->shape.setFillColor(color);
}

void MazeObject::setSize(float width, float height)
{
	this->shape.setSize(sf::Vector2f(width, height));
}

void MazeObject::setOutLine(float think, sf::Color color) {
	this->shape.setOutlineThickness(think);
	this->shape.setOutlineColor(sf::Color(color));
}

void MazeObject::update(const sf::RenderTarget* target)
{
}

void MazeObject::render(sf::RenderTarget* target)
{
	target->draw(this->shape);
}

// Check if a point is in MazeObject (including points on edge)
bool MazeObject::isInMazeObject(const sf::Vector2f& cord) const
{
	sf::Vector2f MazeObjectCord = shape.getPosition();
	sf::Vector2f MazeObjectSize = shape.getSize();

	return (MazeObjectCord.x <= cord.x && cord.x <= MazeObjectCord.x + MazeObjectSize.x &&
		MazeObjectCord.y <= cord.y && cord.y <= MazeObjectCord.y + MazeObjectSize.y);
}

// Check collision between two MazeObjects
bool MazeObject::checkCollision(const MazeObject& other, bool firstCheck) const
{
	// Coordinate and size of other MazeObject
	sf::Vector2f cord = other.shape.getPosition();
	sf::Vector2f size = other.shape.getSize();

	bool areCollided = false;

	areCollided = areCollided || isInMazeObject(cord);
	areCollided = areCollided || isInMazeObject(sf::Vector2f(cord.x + size.x, cord.y));
	areCollided = areCollided || isInMazeObject(sf::Vector2f(cord.x, cord.y + size.y));
	areCollided = areCollided || isInMazeObject(sf::Vector2f(cord.x + size.x, cord.y + size.y));

	if (firstCheck)
		areCollided = areCollided || other.checkCollision(*this, 0);

	return areCollided;
}
