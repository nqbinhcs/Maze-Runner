//#include "Game.hpp"
#include "StateGame.hpp"
#include "StateMenu.hpp"
#include "StateModeSelect.hpp"
#include "StateInGame.hpp"


sf::RenderWindow* SingletonRenderWindow::window = nullptr;

//StateMenu* ContextGame::stateMenu_ = new StateMenu;
//StateModeSelect* ContextGame::stateModeSelect_ = new StateModeSelect;
//StateInGame* ContextGame::stateInGame_ = new StateInGame;

int main()
{
	srand(time(0));

	////Khởi tạo game
	//Game game;
	//Clock clock;
	//float timer = 0, delay = 0.1;
	//
	//
	//while (game.running())
	//{
	//	game.update();
	//	game.render();
	//}

	//return 0;

	ContextGame* context = new ContextGame(new StateMenu);
	while (SingletonRenderWindow::getInstance()->isOpen())
	{
		context->pollEvents();
		context->update();
		context->render();

	}
	

}