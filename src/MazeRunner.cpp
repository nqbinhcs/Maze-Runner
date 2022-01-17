#include "StateGame.hpp"

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