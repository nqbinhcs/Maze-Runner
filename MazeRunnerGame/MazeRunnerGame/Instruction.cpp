#include "Instruction.hpp"

Instruction::Instruction(float width, float height)
{
	if (!textureBackground.loadFromFile(IMG_INSTRUCTION))
	{
		std::cout << "Load file failed" << std::endl;
	}

	spriteBackground.scale(1, 1);
	spriteBackground.setTexture(textureBackground);
	spriteBackground.setPosition(0, 0);
}

void Instruction::draw(sf::RenderWindow& window)
{
	window.draw(spriteBackground);
}

