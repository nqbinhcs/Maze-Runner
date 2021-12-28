#include "HelpAlgorithmMenu.hpp"

HelpAlgorithmMenu::HelpAlgorithmMenu()
{
	//Reload new image
	if (!textureBackground.loadFromFile(IMG_HELP))
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


	//Button
	algos.resize(4);

	int BUTTON_WIDTH = 130;
	int BUTTON_HEIGHT = 100;

	int YPOS = SCREEN_HEIGHT / 2 - 100;
	int XSTART = 332;
	int XPOS[4] = { XSTART, XSTART + 150, XSTART + 300, XSTART + 450 };

	algos[0].setButton(sf::Vector2f(XPOS[0], YPOS), sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Color::Color(240, 186, 74), sf::Color::Transparent,
		"AStar", FONT_GAME, 15, sf::Text::Style::Bold, sf::Color::Black, "");

	algos[1].setButton(sf::Vector2f(XPOS[1], YPOS), sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Color::Color(240, 186, 74), sf::Color::Transparent,
		"BFS", FONT_GAME, 15, sf::Text::Style::Bold, sf::Color::Black, "");

	algos[2].setButton(sf::Vector2f(XPOS[2], YPOS), sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Color::Color(240, 186, 74), sf::Color::Transparent,
		"DFS", FONT_GAME, 15, sf::Text::Style::Bold, sf::Color::Black, "");

	algos[3].setButton(sf::Vector2f(XPOS[3], YPOS), sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
		sf::Color::Color(240, 186, 74), sf::Color::Transparent,
		"Dijkstra", FONT_GAME, 15, sf::Text::Style::Bold, sf::Color::Black, "");

	run.setButton(sf::Vector2f(XPOS[1], YPOS + 130), sf::Vector2f(2 * BUTTON_WIDTH + 20, BUTTON_HEIGHT - 50),
		sf::Color::Color(240, 186, 74), sf::Color::Transparent,
		"RUN", FONT_GAME, 20, sf::Text::Style::Bold, sf::Color::Black, "");

	//choose
	choose = 0;
	algos[0].makeChosen();
	runAlgo = false;
}

HelpAlgorithmMenu::~HelpAlgorithmMenu()
{

}

int HelpAlgorithmMenu::getOptionAlgo()
{
	return choose;
}

bool HelpAlgorithmMenu::isRun()
{
	return runAlgo;
}

bool HelpAlgorithmMenu::isExit(sf::RenderWindow* window)
{

	sf::Vector2i mousePos(sf::Mouse::getPosition(*window));
	sf::FloatRect rect(spriteBackground.getGlobalBounds());

	if (!rect.contains(sf::Vector2f(mousePos.x, mousePos.y)) && sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)
		&& mousePos.x >= 0 && mousePos.x <= SCREEN_WIDTH && mousePos.y >= 0 && mousePos.y <= SCREEN_HEIGHT) return true;
	return false;
}

void HelpAlgorithmMenu::pollEvent(sf::RenderWindow* window)
{

	if (run.isClick(window))
	{
		runAlgo = true;
		return;
	}

	//Select Algo
	for (int i = 0; i < (int)algos.size(); i++)
	{
		if (choose != i && algos[i].isClick(window))
		{
			choose = i;
			algos[i].makeChosen();
		}
	}

	//reset
	for (int i = 0; i < (int)algos.size(); i++)
	{
		if (choose != i)
			algos[i].makeNormal();
	}


	if (choose != -1)
		std::cout << "CLICK " << choose << '\n';
	/*for (int i = 0; i < (int)algos.size(); i++)
	{
		std::cout << "CLICK " << i << ' ' << algos[i].isClick(window) << '\n';
	}*/
}

void HelpAlgorithmMenu::draw(sf::RenderWindow& window)
{
	window.draw(spriteBackground);
	for (int i = 0; i < (int)algos.size(); i++)
	{
		algos[i].drawButton(window);
	}
	run.drawButton(window);
}
