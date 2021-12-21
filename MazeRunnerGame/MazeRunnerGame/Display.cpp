#include "Display.hpp"

//@DESCR: Delay function 
//@PARAM: second.
//@RETURN: None
void delay(float second)
{
	sf::Clock Clock;
	sf::Time timeEnd = sf::seconds(second);
	bool cmp;
	do {
		sf::Time time = Clock.getElapsedTime();
		cmp = (time < timeEnd);
	} while (cmp);
	Clock.restart();
	return;
}

Display::Display()
{
}

Display::Display(float width, float height)
{
	// load file background image
	if (!textureBackground.loadFromFile(IMG_THEME_BACKGROUND))
	{
		std::cout << "Load file failed" << std::endl;
	}

	spriteBackground.setTexture(textureBackground);
	spriteBackground.scale(1, 1);
	spriteBackground.setPosition(0, 0);

}

Display::~Display()
{
}


//@DESCR: Check if the mouse is clicked
//@PARAM: Text : texting, window: to render GUi on
//@RETURN: true if clicked
bool Display::clickMouse(sf::Text Text, sf::RenderWindow& window) // kiểm tra chuôt có click không
{
	sf::IntRect rect(Text.getPosition().x, Text.getPosition().y, Text.getGlobalBounds().width, Text.getGlobalBounds().height);

	if (rect.contains(sf::Mouse::getPosition(window)))
	{
		return true;
	}

	return false;
}

//@DESCR: Set position of the text (the position.X is always the middle width of the screen), the Position.Y is optional by user
//@PARAM: Text : texting, height: the height of the screen
//@RETURN: None
void Display::setPositionText(sf::Text& text, float height)
{
	// Find the rectangle which contains the text
	sf::FloatRect textRect(text.getLocalBounds());
	// Have the rectangle as well as the its coordinates => set origin of text
	text.setOrigin(textRect.left + textRect.width / 2.0f, textRect.top + textRect.height / 2);
	// Set position
	text.setPosition(SCREEN_WIDTH / 2, height);
}

void Display::draw(sf::RenderWindow& window)
{
	window.draw(spriteBackground); // vẽ background menu
	// window.draw(gameName); // vẽ tiêu đề 
}