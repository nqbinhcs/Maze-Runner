#include "Game.hpp"

//using namespace sf;

int main()
{
	srand(time(0));

	//Khởi tạo game
	Game game;
	Clock clock;
	float timer = 0, delay = 0.1;

	//Game loop
	while (game.running())
	{
		game.update();
		game.render();
	}

	return 0;
}