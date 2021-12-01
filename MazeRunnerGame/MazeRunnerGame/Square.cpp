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

float Square::getPositionX()
{
	return this->shape.getPosition().x;
}

float Square::getPositionY()
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
