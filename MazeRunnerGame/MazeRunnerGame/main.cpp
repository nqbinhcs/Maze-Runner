#include "Game.hpp"

//using namespace sf;

int main()
{
	srand(time(0));

	//Khởi tạo game
	Game game;
	Clock clock;
	float timer = 0, delay = 0.1;
	

	game.render();
	
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