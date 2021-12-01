#include "Game.hpp"

//using namespace sf;

int main()
{

	//Khởi tạo game
	Game game;


	//Game loop
	while (game.running())
	{

		game.update();
		game.render();
	}

	return 0;
}