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