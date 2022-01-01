//#include "Game.hpp"
#include "StateGame.hpp"
#include "StateMenu.hpp"
#include "StateModeSelect.hpp"
#include "StateInGame.hpp"


sf::RenderWindow* SingletonRenderWindow::window = nullptr;
int StateModeSelect::pressedItem = 0;

int main()
{
	srand(time(0));

	ContextGame* context = new ContextGame(new StateMenu);
	while (SingletonRenderWindow::getInstance()->isOpen())
	{
		context->pollEvents();
		context->update();
		context->render();

	}

	//clear memory
	

}