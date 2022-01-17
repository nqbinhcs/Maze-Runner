#include "Button.hpp"

bool Button::isClick(sf::RenderWindow* pWindow)
{
	/*std::cout << "Is left mouse pressed : " << sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) << '\n';*/
	if (isMouseover(pWindow) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		return true;
	return false;
}

bool Button::isClickV1(sf::RenderWindow* pWindow)
{
	if (isMouseoverV1(pWindow) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left))
		return true;
	return false;
}

bool Button::isMouseover(sf::RenderWindow* pWindow)
{
	sf::Vector2i mousePos(sf::Mouse::getPosition(*pWindow));

	if (m_Bound.contains(sf::Vector2f(mousePos.x, mousePos.y))) {
		m_isChosen = true;
	}
	else {
		m_isChosen = false;
	}

	return m_isChosen;
}

bool Button::isMouseoverV1(sf::RenderWindow* pWindow)
{
	sf::Vector2i mousePos(sf::Mouse::getPosition(*pWindow));

	if (m_Bound.contains(sf::Vector2f(mousePos.x, mousePos.y))) {
		return true;
	}
	return false;
}

void Button::setTextBox(sf::Vector2f position, sf::Vector2f boxSize,
	sf::Color fillColor, sf::Color outlineColor,
	std::string Text, std::string font,
	float textSize, sf::Uint32 style, sf::Color color)
{

	m_Text.setBox(position, boxSize, fillColor, outlineColor);
	m_Text.setText(Text, font, textSize, style, color);

	m_Text.alignTextCenter();
	m_Text.alignTextMiddle();
}

void Button::setSpriteOriginToCentroid()
{
	sf::FloatRect spriteBound = m_RootSprite.getLocalBounds();
	sf::Vector2f spriteCenter = sf::Vector2f(
		spriteBound.left + spriteBound.width / 2,
		spriteBound.top + spriteBound.height / 2);

	setSpriteOrigin(spriteCenter);
}

void Button::setSpriteOrigin(sf::Vector2f position)
{
	m_RootSprite.setOrigin(position);
	m_ScaleSprite.setOrigin(position);
}

void Button::setSpritePosition(sf::Vector2f position)
{
	m_RootSprite.setPosition(position);
	m_ScaleSprite.setPosition(position);
}

void Button::setSprite(std::string imageFile)
{
	if (!m_Texture.loadFromFile(imageFile)) {
		std::cout << "Load file failed : " << imageFile << std::endl;
	}
	else std::cout << imageFile << '\n';

	m_RootSprite.setTexture(m_Texture);

	setSpriteOriginToCentroid();

	m_ScaleSprite = m_RootSprite;
}

void Button::scaleSprite(float scaleSize)
{
	m_ScaleSprite = m_RootSprite;
	m_ScaleSprite.scale(sf::Vector2f(scaleSize, scaleSize));
}

void Button::setScaleSprite(sf::Vector2f scale)
{
	m_RootSprite.setScale(scale);
}

sf::Vector2f Button::getScaleSprite()
{
	return m_RootSprite.getScale();
}


void Button::setButton(sf::Vector2f position, sf::Vector2f boxSize,
	sf::Color fillColor, sf::Color outlineColor,
	std::string text, std::string font,
	float textSize, sf::Uint32 style, sf::Color color,
	std::string imageFile)
{
	setTextBox(position, boxSize, fillColor, outlineColor,
		text, font, textSize, style, color);

	if (imageFile != "")
	{
		setSprite(imageFile);

		sf::FloatRect spriteBound = m_RootSprite.getGlobalBounds();
		sf::Vector2f boxCenter = sf::Vector2f(
			m_Text.m_Bound.top + m_Text.m_Bound.height / 2,
			m_Text.m_Bound.left + m_Text.m_Bound.width / 2);

		m_RootSprite.setScale(sf::Vector2f(m_Text.m_Bound.width / spriteBound.width, m_Text.m_Bound.height / spriteBound.height));
		setSpriteOriginToCentroid();
		setSpritePosition(position);

		m_ScaleSprite = m_RootSprite;
	}

	updateBound();
}

void Button::setButton(sf::Vector2f position, std::string imageFile, float spriteScale)
{
	setSprite(imageFile);
	setSpritePosition(position);
	scaleSprite(spriteScale);

	updateBound();
}

void Button::updateBound()
{
	sf::FloatRect textBound(m_Text.m_Bound);
	sf::FloatRect textureBound(m_Text.m_Bound);

	m_Bound = textBound;
}

void Button::scale(float scaleSize)
{
	m_Text.scale(scaleSize);
	scaleSprite(scaleSize);

	updateBound();
}

void Button::makeChosen()
{
	m_isChosen = true;
	scale(CHOSEN_BUTTON_SIZE);
}

void Button::makeNormal()
{
	m_isChosen = false;
	scale(NORMAL_BUTTON_SIZE);
}

bool Button::isChosen()
{
	return m_isChosen;
}

void Button::drawButton(sf::RenderTarget& window)
{
	window.draw(m_ScaleSprite);
	m_Text.drawMyText(window);
}