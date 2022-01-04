#include "GameOver.hpp"


GameOver::GameOver()
{
	
}

GameOver::GameOver(float width, float height)
{
	if (!textureBackground.loadFromFile(IMG_GAMEOVER))
	{
		std::cout << "Load file failed" << std::endl;
	}

	spriteBackground.setTexture(textureBackground);
	spriteBackground.scale(1, 1);
	spriteBackground.setPosition(0, 0);

}

GameOver::~GameOver()
{
}

void GameOver::draw(sf::RenderWindow &window)
{	
		window.draw(spriteBackground); 
}
