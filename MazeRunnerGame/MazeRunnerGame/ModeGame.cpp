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

	/* set thông số đồ họa cho dòng chữ NEW GAME
	   do dònng chữ New Game nằm đầu nên ta cho mặc định khi vào Menu, chức năng này được chọn */

	int delta = 70;
	textMode[0].setFont(font);
	textMode[0].setCharacterSize(60);
	textMode[0].setFillColor(sf::Color::White);
	textMode[0].setStyle(sf::Text::Bold);
	textMode[0].setString("EASY");
	setPositionText(textMode[0], 200 + delta);

	// set thông số đồ họa cho dòng chữ các dòng chữ thể hiện chức năng khác
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

	select = 0; // mặc định ban đầu chọn chức năng 1
}

void ModeGame::draw(sf::RenderWindow& window)
{
	Display::draw(window); // vẽ lại Background trong Display
	for (int i = 0; i < 3; i++)
	{
		window.draw(textMode[i]); // vẽ các dòng chữ thể hiện chế độ chơi
	}
}

void ModeGame::moveUp() // nhấn phím UP
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

void ModeGame::moveDown() // nhấn phím Down
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
	/*  khi di chuyển chuột đên một dòng chữ nào đó
		dòng chữ đó sẽ đổi sang màu trắng và size lớn hơn bình thường
		các dòng chữ còn lại màu đỏ và size bình thường
		cập nhật là select
	*/
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

//int ModeGame::mouseSelect(sf::RenderWindow& window) // bắt sự kiện click chuột
//{
//	levelChoice choice(window.getSize().x, window.getSize().y);
//
//	if (clickMouse(textMode[0], window))
//	{
//		choice.runLevelChoice(window, GetPressedItem());
//		return 0; // player chơi
//	}
//	if (clickMouse(textMode[1], window))
//	{
//		choice.runLevelChoice(window, GetPressedItem()); // máy chơi
//		return 1;
//	}
//
//	return -1;
//}
//
//int ModeGame::mouseSelectHigh(sf::RenderWindow& window)
//{
//
//	if (clickMouse(textMode[0], window))
//	{
//		listHighScore listHigh(window.getSize().x, window.getSize().y, GetPressedItem());
//		listHigh.drawMenu(window, GetPressedItem());
//		return 0; // player chơi
//	}
//	if (clickMouse(textMode[1], window))
//	{
//		listHighScore listHigh(window.getSize().x, window.getSize().y, GetPressedItem());
//		listHigh.drawMenu(window, GetPressedItem());
//		return 1;
//	}
//
//	return -1;
//}
//
void ModeGame::runModeGame(sf::RenderWindow& window)
{
	while (window.isOpen()) {
		sf::Event event;
		while(window.pollEvent(event)) {
			switch (event.type) {

			case sf::Event::Closed:
				window.close();
				break;
			case sf::Event::MouseMoved:
				mouseMoved(window); // di chuyển chuột
				break;
			case sf::Event::MouseButtonPressed:
			{
				mouseSelect(window); // click chuột
				break;
			}

			case sf::Event::KeyPressed:

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
					moveUp(); // di chuyển lên
				}
				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
					moveDown(); // di chuyển xuống
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
					return;
				}

				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
					return;
				}
			}
		}
		window.clear();
		draw(window);
		window.display();
		//return GetPressedItem();
	}
}
//
//void ModeGame::runModeHigh(sf::RenderWindow& window)
//{
//	while (window.isOpen()) {
//		sf::Event event;
//		while (window.pollEvent(event)) {
//			switch (event.type) {
//
//			case sf::Event::Closed:
//				window.close();
//				break;
//			case sf::Event::MouseMoved:
//				mouseMoved(window); // di chuyển chuột
//				break;
//			case sf::Event::MouseButtonPressed:
//			{
//				mouseSelectHigh(window); // click chuột
//				break;
//			}
//
//			case sf::Event::KeyPressed:
//
//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
//					moveUp(); // di chuyển lên
//				}
//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
//					moveDown(); // di chuyển xuống
//				}
//
//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
//					return;
//				}
//
//				if (sf::Keyboard::isKeyPressed(sf::Keyboard::Return)) {
//
//					listHighScore listHigh(window.getSize().x, window.getSize().y, GetPressedItem());
//					listHigh.drawMenu(window, GetPressedItem());
//				}
//			}
//		}
//		window.clear();
//		drawMenu(window);
//		window.display();
//	}
//}
//
int ModeGame::GetPressedItem() // lấy giá trị select
{
	return select;
}
