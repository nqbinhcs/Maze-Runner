#include "Menu.hpp"
//#include "modeGame.hpp"

Menu::Menu()
{

}
Menu::Menu(float width, float height) :Display(width, height)
{
	if (!font.loadFromFile("Fonts/TitleFont.ttf"))
	{
		std::cout << "Load font failed" << std::endl;
	}

	/* set thông số đồ họa cho dòng chữ NEW GAME
	   do dònng chữ New Game nằm đầu nên ta cho mặc định khi vào Menu, chức năng này được chọn */

	
	delta_effect = 120;

	int delta = 100;
	GameTittle.setFont(font);
	GameTittle.setCharacterSize(100);
	GameTittle.setFillColor(sf::Color::Color(220, 220, 215));
	GameTittle.setStyle(sf::Text::Bold | sf::Text::Underlined | sf::Text::Italic);
	GameTittle.setString("MAZE RUNNER");
	setPositionText(GameTittle, 150);


	text[0].setFont(font);
	text[0].setCharacterSize(60);
	text[0].setFillColor(sf::Color::White);
	text[0].setStyle(sf::Text::Bold);
	text[0].setString("NEW GAME");

	setPositionText(text[0], 170 + delta);

	// set thông số đồ họa cho dòng chữ các dòng chữ thể hiện chức năng khác
	setText(1, "CONTINUE GAME");
	setPositionText(text[1], 250 + delta);

	setText(2, "HIGH SCORE");
	setPositionText(text[2], 330 + delta);

	setText(3, "HELP");
	setPositionText(text[3], 410 + delta);

	setText(4, "EXIT GAME");
	setPositionText(text[4], 490 + delta);

	selectOption = 0; // mặc định ban đầu chọn chức năng 1
}

Menu::~Menu()
{

}

void Menu::setText(int select, std::string nameOption)
{
	// set thông số đồ họa cho text
	text[select].setFont(font);
	text[select].setCharacterSize(40);
	text[select].setFillColor(sf::Color::White);
	text[select].setStyle(sf::Text::Bold);
	text[select].setString(nameOption);
}

void Menu::draw(sf::RenderWindow& window)
{
	Display::draw(window); // vẽ lại Background trong Display

	//effect for fun
	delta_effect *= -1;
	GameTittle.setFillColor(sf::Color::Color(120 + delta_effect, 120 + delta_effect, 120 + delta_effect));
	window.draw(GameTittle);
	for (int i = 0; i < _MAX_CHOICE_MENU; i++)
	{
		window.draw(text[i]); // vẽ các dòng chữ thể hiện chế độ chơi
	}
}

void Menu::moveUp() // nhấn phím UP
{
	if (selectOption - 1 >= 0) // do đi lên nên kiểm tra >= 0
	{
		text[selectOption].setFillColor(sf::Color::White);
		text[selectOption].setCharacterSize(40);

		// update position because changing size
		setPositionText(text[selectOption], 270 + selectOption * 80);

		selectOption--;

		text[selectOption].setFillColor(sf::Color::White);
		text[selectOption].setCharacterSize(60);

		// update position because changing size
		setPositionText(text[selectOption], 270 + selectOption * 80);
	}
}

void Menu::moveDown() // nhấn phím DOWN
{
	if (selectOption + 1 < _MAX_CHOICE_MENU) // do đi xuống nên kiểm tra < _MAX_CHOICE_MENU
	{
		text[selectOption].setFillColor(sf::Color::White);
		text[selectOption].setCharacterSize(40);

		// update position because changing size
		setPositionText(text[selectOption], 270 + selectOption * 80);

		selectOption++;
		text[selectOption].setFillColor(sf::Color::White);
		text[selectOption].setCharacterSize(60);

		// update position because changing size
		setPositionText(text[selectOption], 270 + selectOption * 80);
	}
}


void Menu::mouseMoved(sf::RenderWindow& windows) // di chuyển chuột
{/*  khi di chuyển chuột đên một dòng chữ nào đó
		dòng chữ đó sẽ đổi sang màu trắng và size lớn hơn bình thường
		các dòng chữ còn lại màu đỏ và size bình thường
		cập nhật là selectOption
	*/
	if (clickMouse(text[0], windows))
	{
		selectOption = 0;

		text[0].setFillColor(sf::Color::White);
		text[1].setFillColor(sf::Color::White);
		text[2].setFillColor(sf::Color::White);
		text[3].setFillColor(sf::Color::White);
		text[4].setFillColor(sf::Color::White);

		text[0].setCharacterSize(60);
		text[1].setCharacterSize(40);
		text[2].setCharacterSize(40);
		text[3].setCharacterSize(40);
		text[4].setCharacterSize(40);

		// update position because changing size
		setPositionText(text[0], 170);
		setPositionText(text[1], 250);
		setPositionText(text[2], 330);
		setPositionText(text[3], 410);
		setPositionText(text[4], 490);
	}

	else if (clickMouse(text[1], windows))
	{
		text[0].setFillColor(sf::Color::White);
		text[1].setFillColor(sf::Color::White);
		text[2].setFillColor(sf::Color::White);
		text[3].setFillColor(sf::Color::White);
		text[4].setFillColor(sf::Color::White);

		text[0].setCharacterSize(40);
		text[1].setCharacterSize(60);
		text[2].setCharacterSize(40);
		text[3].setCharacterSize(40);
		text[4].setCharacterSize(40);

		selectOption = 1;

		// update position because changing size
		setPositionText(text[0], 170);
		setPositionText(text[1], 250);
		setPositionText(text[2], 330);
		setPositionText(text[3], 410);
		setPositionText(text[4], 490);
	}

	else if (clickMouse(text[2], windows))
	{
		text[0].setFillColor(sf::Color::White);
		text[1].setFillColor(sf::Color::White);
		text[2].setFillColor(sf::Color::White);
		text[3].setFillColor(sf::Color::White);
		text[4].setFillColor(sf::Color::White);

		text[0].setCharacterSize(40);
		text[1].setCharacterSize(40);
		text[2].setCharacterSize(60);
		text[3].setCharacterSize(40);
		text[4].setCharacterSize(40);

		selectOption = 2;

		// update position because changing size
		sf::FloatRect textRect(text[0].getLocalBounds());
		setPositionText(text[0], 170);
		setPositionText(text[1], 250);
		setPositionText(text[2], 330);
		setPositionText(text[3], 410);
		setPositionText(text[4], 490);
	}

	else if (clickMouse(text[3], windows))
	{
		text[0].setFillColor(sf::Color::White);
		text[1].setFillColor(sf::Color::White);
		text[2].setFillColor(sf::Color::White);
		text[3].setFillColor(sf::Color::White);
		text[4].setFillColor(sf::Color::White);

		text[0].setCharacterSize(40);
		text[1].setCharacterSize(40);
		text[2].setCharacterSize(40);
		text[3].setCharacterSize(60);
		text[4].setCharacterSize(40);

		selectOption = 3;

		// update position because changing size
		setPositionText(text[0], 170);
		setPositionText(text[1], 250);
		setPositionText(text[2], 330);
		setPositionText(text[3], 410);
		setPositionText(text[4], 490);
	}

	else if (clickMouse(text[4], windows))
	{
		text[0].setFillColor(sf::Color::White);
		text[1].setFillColor(sf::Color::White);
		text[2].setFillColor(sf::Color::White);
		text[3].setFillColor(sf::Color::White);
		text[4].setFillColor(sf::Color::White);

		text[0].setCharacterSize(40);
		text[1].setCharacterSize(40);
		text[2].setCharacterSize(40);
		text[3].setCharacterSize(40);
		text[4].setCharacterSize(60);

		selectOption = 4;

		// update position because changing size
		setPositionText(text[0], 170);
		setPositionText(text[1], 250);
		setPositionText(text[2], 330);
		setPositionText(text[3], 410);
		setPositionText(text[4], 490);
	}
}

void Menu::mouseSelect(sf::RenderWindow& window) // bắt sự kiện click chuột
{
	if (clickMouse(text[0], window)) // vào chọn chế độ chơi
	{
		//modeGame mode(window.getSize().x, window.getSize().y);
		//mode.runModeGame(window);
	}
	else if (clickMouse(text[1], window)) // vào chức năng tiếp tục chơi
	{
		//continueGame cont;
		//cont.runContinueGame(window);
	}
	else if (clickMouse(text[2], window)) // hiện bảng điểm cao
	{
		//modeGame mode(window.getSize().x, window.getSize().y);
		//mode.runModeHigh(window);
	}
	else if (clickMouse(text[3], window)) // hiện bảng giúp đỡ
	{
		//helpMenu help(window.getSize().x, window.getSize().y);
		//help.drawMenu(window);
	}
	else if (clickMouse(text[4], window)) // thoát game
	{
		window.close();
	}
}

int Menu::GetPressedItem() // lấy giá trị selectOption
{
	return selectOption;
}
