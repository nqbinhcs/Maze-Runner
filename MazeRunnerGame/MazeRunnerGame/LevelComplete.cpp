#include "LevelComplete.hpp"

LevelComplete::LevelComplete()
{

	// Load BackGround
	if (!textureBackground.loadFromFile(IMG_LEVELCOMPLETE))
	{
		std::cout << "Load file failed" << std::endl;
	}

	spriteBackground.setTexture(textureBackground);

	sf::Vector2u textureBackgroundSize = textureBackground.getSize();
	textureBackgroundSize.x /= 2;
	textureBackgroundSize.y /= 2;

	spriteBackground.setOrigin(textureBackgroundSize.x, textureBackgroundSize.y);

	spriteBackground.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	spriteBackground.scale(0.75, 0.75);


	// Load total time text
	font.loadFromFile(FONT_GAME);

	text.setFont(font);
	text.setCharacterSize(40);
	text.setFillColor(sf::Color::Cyan);
	text.setStyle(sf::Text::Bold);

}

LevelComplete::~LevelComplete()
{
}


//@DESCR: Render the level complete screen
//@PARAM: m_pWindow to render GUi on, time: total time stat of the player
//@RETURN: None
void LevelComplete::draw(sf::RenderWindow& window, int time)
{
	//Draw background
	window.draw(spriteBackground);

	//Draw text
	std::stringstream ss;
	ss << "TIME " << time << "S";
	std::string timeText = ss.str();
	text.setString(timeText);
	//The condition to use setPosition, a string must have a particular value
	setPositionText(text, SCREEN_HEIGHT / 2 + 70);
	window.draw(text);
}
