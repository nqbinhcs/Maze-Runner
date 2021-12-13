#include "NextStage.hpp"


NextStage::NextStage()
{
	if (!textureBackground.loadFromFile(IMG_NEXTSTAGE))
	{
		std::cout << "Load file failed" << std::endl;
	}

	spriteBackground.setTexture(textureBackground);

	sf::Vector2u textureBackgroundSize = textureBackground.getSize();
	textureBackgroundSize.x /= 2;
	textureBackgroundSize.y /= 2;

	spriteBackground.setOrigin(textureBackgroundSize.x, textureBackgroundSize.y);

	spriteBackground.setPosition(SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);

	spriteBackground.scale(0.5, 0.5);
}

NextStage::~NextStage()
{
}
