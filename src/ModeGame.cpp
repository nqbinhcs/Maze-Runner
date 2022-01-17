#include "ModeGame.hpp"


ModeGame::ModeGame()
{

}

ModeGame::~ModeGame()
{

}

ModeGame::ModeGame(float width, float height) :Menu(width, height)
{
	if (!font.loadFromFile("Fonts/TitleFont.ttf"))
	{
		std::cout << "Load font failed" << std::endl;
	}


	int delta = 70;
	textMode[0].setFont(font);
	textMode[0].setCharacterSize(60);
	textMode[0].setFillColor(sf::Color::White);
	textMode[0].setStyle(sf::Text::Bold);
	textMode[0].setString("EASY");
	setPositionText(textMode[0], 200 + delta);

	
	textMode[1].setFont(font);
	textMode[1].setCharacterSize(40);
	textMode[1].setFillColor(sf::Color::White);
	textMode[1].setStyle(sf::Text::Bold);
	textMode[1].setString("NORMAL");
	setPositionText(textMode[1], 300 + delta);

	textMode[2].setFont(font);
	textMode[2].setCharacterSize(40);
	textMode[2].setFillColor(sf::Color::White);
	textMode[2].setStyle(sf::Text::Bold);
	textMode[2].setString("HARD");
	setPositionText(textMode[2], 400 + delta);

	select = 0; 
}

void ModeGame::draw(sf::RenderWindow& window)
{
	Display::draw(window); 
	for (int i = 0; i < 3; i++)
	{
		window.draw(textMode[i]); 
	}
}

void ModeGame::moveUp() 
{
	int delta = 70;
	if (select - 1 >= 0)
	{
		textMode[select].setFillColor(sf::Color::White);
		textMode[select].setCharacterSize(40);

		// update position because changing size
		setPositionText(textMode[select], 200 + delta + select * 100);

		select--;

		textMode[select].setFillColor(sf::Color::White);
		textMode[select].setCharacterSize(60);

		// update position because changing size
		setPositionText(textMode[select], 200 + delta + select * 100);
	}
}

void ModeGame::moveDown() 
{
	int delta = 70;
	if (select + 1 < 3)
	{
		textMode[select].setFillColor(sf::Color::White);
		textMode[select].setCharacterSize(40);

		// update position because changing size
		setPositionText(textMode[select], 200 + delta + select * 100);

		select++;
		textMode[select].setFillColor(sf::Color::White);
		textMode[select].setCharacterSize(60);

		// update position because changing size
		setPositionText(textMode[select], 200 + delta + select * 100);
	}
}

void ModeGame::mouseMoved(sf::RenderWindow& windows) // di chuyển chuột
{
	if (clickMouse(textMode[0], windows))
	{
		select = 0;

		textMode[0].setFillColor(sf::Color::White);
		textMode[1].setFillColor(sf::Color::Yellow);

		textMode[0].setCharacterSize(60);
		textMode[1].setCharacterSize(40);

		// update position because changing size
		setPositionText(textMode[0], 200);
		setPositionText(textMode[1], 300);
	}

	if (clickMouse(textMode[1], windows))
	{
		select = 1;

		textMode[0].setFillColor(sf::Color::Yellow);
		textMode[1].setFillColor(sf::Color::White);

		textMode[0].setCharacterSize(40);
		textMode[1].setCharacterSize(60);

		// update position because changing size
		setPositionText(textMode[0], 200);
		setPositionText(textMode[1], 300);
	}
}

int ModeGame::GetPressedItem() // lấy giá trị select
{
	return select;
}
