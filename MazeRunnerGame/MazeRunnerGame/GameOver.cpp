#include "GameOver.hpp"


GameOver::GameOver()
{
	
}

GameOver::GameOver(float width, float height) : Display(width, height)
{
	/*if (!textureBackground.loadFromFile(IMG_GAMEOVER))
	{
		std::cout << "Load file failed" << std::endl;
	}

	spriteBackground.setTexture(textureBackground);
	spriteBackground.scale(1, 1);
	spriteBackground.setPosition(0, 0);*/


	text.setBox(sf::Vector2f(0, 0),
		sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT),
		sf::Color::Black, sf::Color::Transparent);
	text.setText("GAME OVER", FONT_GAME, 100, sf::Text::Bold, sf::Color::White);
	text.setCharacterSpacing(1.5);
	text.alignTextCenter();
	text.alignTextMiddle();
	text.setBoxOutlineThickness(100);
	text.setBoxOutlineColor(sf::Color::White);

	smallText.resize(1);

	smallText[0].setText("GUD LUCK ON YOUR NEXT GAME!", SECOND_FONT_GAME, 50, sf::Text::Bold, sf::Color::White);
	smallText[0].setCharacterSpacing(1.5);
	smallText[0].alignTextCenter();
	smallText[0].setTextPosition(SCREEN_WIDTH / 2, 500);

}

GameOver::~GameOver()
{
}

void GameOver::draw(sf::RenderWindow &window)
{	
		//std::cout << "CALL GAMEOVER DRAW\n";
		window.draw(spriteBackground); // vẽ background menu
		text.drawMyText(window);
		smallText[0].drawMyText(window);
		// window.draw(gameName); // vẽ tiêu đề 
}
