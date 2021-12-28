#include "Game.hpp"
//VGIT
//using namespace sf;

int main()
{
	srand(time(0));

	//Khởi tạo game
	Game game;
	Clock clock;
	float timer = 0, delay = 0.1;
	
	//Button m_Help;
	//cout << OFFSET_HELP_X << " " << OFFSET_HELP_Y << " " << BUTTON_WIDTH << " " << BUTTON_HEIGHT << endl;
	//m_Help.setButton(sf::Vector2f(10, 10), sf::Vector2f(BUTTON_WIDTH, BUTTON_HEIGHT),
	//	sf::Color::Black, sf::Color::Black,
	//	"Help", FONT_GAME, 32, sf::Text::Style::Bold, sf::Color::White, "");
	//cout << m_Help.m_Text.getTextPositionX() << " " << m_Help.m_Text.getTextPositionY() << endl;
	////MyText a("ahihi", FONT_GAME, 30, sf::Text::Style::Bold, sf::Color::Red);
	//{

	//	game.m_pWindow->clear(sf::Color::White);
	//	m_Help.drawButton(*game.m_pWindow);
	//	m_Help.m_Text.drawMyText(*game.m_pWindow);
	//	game.m_pWindow->display();
	//}
	// char c;
	// cin >> c;
		//game.render();
	//
	//Game loop
	while (game.running())
	{
		game.update();
		game.render();
	}

	return 0;
	//sf::RenderWindow window(sf::VideoMode(640, 640), "SFML works!");
	//sf::Text text;

	//// select the font
	//text.setFont(FONT_GAME); // font is a sf::Font

	//// set the string to display
	//text.setString("Hello world");

	//// set the character size
	//text.setCharacterSize(24); // in pixels, not points!

	//// set the color
	//text.setFillColor(sf::Color::Red);

	//// set the text style
	//text.setStyle(sf::Text::Bold | sf::Text::Underlined);

	//while (window.isOpen())
	//{
	//	sf::Event event;
	//	while (window.pollEvent(event))
	//	{
	//		if (event.type == sf::Event::Closed)
	//			window.close();
	//	}

	//	window.clear(sf::Color(255,255,255));
	//	/*shared_ptr<Player> player;
	//	MazeCoordinate pos(0, 1);
	//	player = std::shared_ptr<Player>(new Player(pos, OFFSET_MAZE_X, OFFSET_MAZE_Y, int(SCREEN_MAZE_WIDTH / MAZE_X), int(SCREEN_MAZE_WIDTH / MAZE_X)));
	//	player->render(window);*/
	//	window.display();

	//	// inside the main loop, between window.clear() and window.display()
	//	window.draw(text);
	//}

	//return 0;

}